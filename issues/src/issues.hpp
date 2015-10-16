
#ifndef ISSUES_HPP
#define ISSUES_HPP


// Represents the entirety of the XML issues data.
struct IssuesList 
{
   explicit IssuesList(string const& path);

   auto get_doc_number(string doc) const -> string;
   auto get_intro(string doc) const -> string;
   auto get_maintainer() const -> string;
   auto get_revision() const -> string;
   auto get_revisions(vector<issue> const& issues, string const& diff_report) const -> string;
   auto get_statuses() const -> string;

private:
   string m_data;
};

IssuesList::IssuesList(string const& path)
   : m_data()
{
   ifstream infile{(path + "ts-issues.xml").c_str()};
   if (!infile.is_open()) {
      throw runtime_error{"Unable to open ts-issues.xml"};
   }

   istreambuf_iterator<char> first{infile}, last{};
   m_data.assign(first, last);
}


auto IssuesList::get_doc_number(string doc) const -> string {
    if (doc == "active") {
        doc = "active_docno=\"";
    }
    else if (doc == "complete") {
        doc = "defect_docno=\"";
    }
    else if (doc == "closed") {
        doc = "closed_docno=\"";
    }
    else {
        throw runtime_error{"unknown argument to get_doc_number: " + doc};
    }

    auto i = m_data.find(doc);
    if (i == string::npos) {
        throw runtime_error{"Unable to find docno in ts-issues.xml"};
    }
    i += doc.size();
    auto j = m_data.find('\"', i+1);
    if (j == string::npos) {
        throw runtime_error{"Unable to parse docno in ts-issues.xml"};
    }
    return m_data.substr(i, j-i);
}

auto IssuesList::get_intro(string doc) const -> string {
    if (doc == "active") {
        doc = "<intro list=\"Active\">";
    }
    else if (doc == "complete") {
        doc = "<intro list=\"Complete\">";
    }
    else if (doc == "closed") {
        doc = "<intro list=\"Closed\">";
    }
    else {
        throw runtime_error{"unknown argument to intro: " + doc};
    }

    auto i = m_data.find(doc);
    if (i == string::npos) {
        throw runtime_error{"Unable to find intro in ts-issues.xml"};
    }
    i += doc.size();
    auto j = m_data.find("</intro>", i);
    if (j == string::npos) {
        throw runtime_error{"Unable to parse intro in ts-issues.xml"};
    }
    return m_data.substr(i, j-i);
}


auto IssuesList::get_maintainer() const -> string {
   auto i = m_data.find("maintainer=\"");
   if (i == string::npos) {
      throw runtime_error{"Unable to find maintainer in ts-issues.xml"};
   }
   i += sizeof("maintainer=\"") - 1;
   auto j = m_data.find('\"', i);
   if (j == string::npos) {
      throw runtime_error{"Unable to parse maintainer in ts-issues.xml"};
   }
   string r = m_data.substr(i, j-i);
   auto m = r.find("&lt;");
   if (m == string::npos) {
      throw runtime_error{"Unable to parse maintainer email address in ts-issues.xml"};
   }
   m += sizeof("&lt;") - 1;
   auto me = r.find("&gt;", m);
   if (me == string::npos) {
      throw runtime_error{"Unable to parse maintainer email address in ts-issues.xml"};
   }
   string email = r.substr(m, me-m);
   // &lt;                                    ewgchair@gmail.com    &gt;
   // &lt;<a href="mailto:ewgchair@gmail.com">ewgchair@gmail.com</a>&gt;
   r.replace(m, me-m, "<a href=\"mailto:" + email + "\">" + email + "</a>");
   return r;
}


auto IssuesList::get_revision() const -> string {
    auto i = m_data.find("revision=\"");
    if (i == string::npos) {
        throw runtime_error{"Unable to find revision in ts-issues.xml"};
    }
    i += sizeof("revision=\"") - 1;
    auto j = m_data.find('\"', i);
    if (j == string::npos) {
        throw runtime_error{"Unable to parse revision in ts-issues.xml"};
    }
    return m_data.substr(i, j-i);
}


auto IssuesList::get_revisions(vector<issue> const& issues, string const& diff_report) const -> string {
   auto i = m_data.find("<revision_history>");
   if (i == string::npos) {
      throw runtime_error{"Unable to find <revision_history> in ts-issues.xml"};
   }
   i += sizeof("<revision_history>") - 1;

   auto j = m_data.find("</revision_history>", i);
   if (j == string::npos) {
      throw runtime_error{"Unable to find </revision_history> in ts-issues.xml"};
   }
   auto s = m_data.substr(i, j-i);
   j = 0;

   // bulding a potentially large string, would a stringstream be a better solution?
   // Probably not - string will not be *that* big, and stringstream pays the cost of locales
   string r = "<ul>\n";

   r += "<li>";
//   r += "R74: 2011-02-28 pre-Madrid mailing";   // This is the form we are copying
//   r += "R01: 2013-03-18 pre-Bristol mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//   r += "D02: 2013-04-28 updated tiny issue statuses";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//   r += "R02: 2013-05-06 post-Bristol mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//     r += "R03: 2013-08-27 pre-Chicago mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//     r += "R04: 2013-10-11 post-Chicago mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//     r += "R05: 2014-01-17 pre-Issaquah mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//     r += "R06: 2014-02-21 post-Issaquah mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//     r += "R07: 2014-05-20 pre-Rapperswil mailing";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//     r += "D08: 2014-06-01 working draft";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
//       r += "R08: 2014-07-02 post-Rapperswil mailing";
//   r += "D09: 2014-07-02 working version";
//   r += "R09: 2014-10-09 pre-Urbana mailing";
//   r += "R10: 2014-10-29 post-Urbana mailing";
//
   r += "R12: 2015-05-22 post-Lenexa mailing";
//   r += "Madrid meeting resolutions";   // We should date and *timestamp* this reference, as we expect to generate several documents per day
   r += diff_report;
   r += "</li>\n";

   while (true) {
      i = s.find("<revision tag=\"", j);
      if (i == string::npos) {
         break;
      }
      i += sizeof("<revision tag=\"") - 1;
      j = s.find('\"', i);
      string const rv = s.substr(i, j-i);
      i = j+2;
      j = s.find("</revision>", i);

      r += "<li>";
      r += rv + ": ";
      r += s.substr(i, j-i);
      r += "</li>\n";
   }
   r += "</ul>\n";

   replace_all_irefs(issues, r);

   return r;
}


auto IssuesList::get_statuses() const -> string {
   auto i = m_data.find("<statuses>");
   if (i == string::npos) {
      throw runtime_error{"Unable to find statuses in ts-issues.xml"};
   }
   i += sizeof("<statuses>") - 1;

   auto j = m_data.find("</statuses>", i);
   if (j == string::npos) {
      throw runtime_error{"Unable to parse statuses in ts-issues.xml"};
   }
   return m_data.substr(i, j-i);
}
