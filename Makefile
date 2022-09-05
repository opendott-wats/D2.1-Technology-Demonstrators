# Make sure you change the filename from Paper.md to something meaningful.
TITLE := D2.1 Technology Demonstrators
SOURCE := ReadMe.md

# Replace all spaces with - to make it path safe
TARGET_NAME := $(subst $() $(),-,$(TITLE))

HTML :=  index.html
PDF := $(TARGET_NAME).pdf
DOCX := $(TARGET_NAME).docx
ARCHIVE := $(TARGET_NAME).zip

# STYLE := _pandoc/pandoc.css
# Source: https://gist.github.com/killercup/5917178
# Make sure you save this in the same directory as shown or change the path.

OPTS :=  --from=markdown+smart+simple_tables+table_captions+yaml_metadata_block+smart

ARGS := \
	--filter pandoc-crossref \
	--citeproc
	# --csl=.styles/acm-sig-proceedings-long-author-list.csl \
	# --toc

.PHONY : archive
archive: $(ARCHIVE)
$(ARCHIVE) : .*
	git archive -o $(ARCHIVE) HEAD
	git submodule --quiet foreach 'cd "$$toplevel"; zip -ru --exclude=*.git* $(ARCHIVE) "$$sm_path"'
	zip -ru $(ARCHIVE) D2.1-Technology-Demonstrators.docx
	zip -ru $(ARCHIVE) D2.1-Technology-Demonstrators.pdf

.PHONY : info
info:
	@echo --- Input ---
	@echo $(SOURCE)
	@echo --- Output ---
	@echo $(PDF)
	@echo $(HTML)
	@echo $(DOCX)


.PHONY : watch
watch:
	@echo ------ Building on file changes -----
	@ls *.md | entr make acm

.PHONY : all
all : $(HTML) $(PDF) $(DOCX) $(ARCHIVE)

.PHONY : html
html: $(HTML)
$(HTML) : $(SOURCE)
	@echo --- Generating HTML ---
	@pandoc $(OPTS)+ascii_identifiers $(ARGS) -s -w html \
		--embed-resources --standalone \
		--default-image-extension=png \
		--mathjax \
		--metadata link-citations=true \
		--metadata linkReferences=true \
		-o $@ $<

.PHONY : pdf
pdf : $(PDF)
$(PDF) : $(SOURCE)
	@echo --- Generating PDF ---
	@pandoc $(OPTS)+raw_tex $(ARGS) -t pdf \
		--shift-heading-level-by=-1 \
		--default-image-extension=pdf \
		-V colorlinks=true \
		-V linkcolor=blue \
		-V urlcolor=blue \
		-V toccolor=gray \
		-V documentclass=article \
		-V papersize:a4 \
		-V geometry:a4paper \
		--pdf-engine xelatex \
		-o $@ $<

.PHONY : doc
doc: $(DOCX)
$(DOCX) : $(SOURCE)
	@echo --- Generating DOCX ---
	@pandoc $(OPTS) $(ARGS) -w docx \
		--katex \
		--default-image-extension=png \
		-o $@ $<
# --reference-doc=_pandoc/base.docx

.PHONY : clean
clean :
	@echo --- Deleting generated files ---
	@-rm $(HTML) $(PDF) $(DOCX) $(ARCHIVE)
