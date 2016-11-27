

src = post-issaquah-2016

pdf: ${src}.md
	pandoc ${src}.md -o ${src}.pdf

html: ${src}.md
	pandoc ${src}.md -o ${src}.html

all: pdf html

clean:
	rm -f ${src}.pdf
