/* wgEncodeGencodeEntrezGene.h was originally generated by the autoSql program, which also 
 * generated wgEncodeGencodeEntrezGene.c and wgEncodeGencodeEntrezGene.sql.  This header links the database and
 * the RAM representation of objects. */

#ifndef WGENCODEGENCODEENTREZGENE_H
#define WGENCODEGENCODEENTREZGENE_H

#define WGENCODEGENCODEENTREZGENE_NUM_COLS 2

extern char *wgEncodeGencodeEntrezGeneCommaSepFieldNames;

struct wgEncodeGencodeEntrezGene
/* The NCBI Entrez gene id associated with GENCODE transcript annotation */
    {
    struct wgEncodeGencodeEntrezGene *next;  /* Next in singly linked list. */
    char *transcriptId;	/* GENCODE transcript identifier */
    int entrezGeneId;	/* Entrez gene id */
    };

void wgEncodeGencodeEntrezGeneStaticLoad(char **row, struct wgEncodeGencodeEntrezGene *ret);
/* Load a row from wgEncodeGencodeEntrezGene table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct wgEncodeGencodeEntrezGene *wgEncodeGencodeEntrezGeneLoad(char **row);
/* Load a wgEncodeGencodeEntrezGene from row fetched with select * from wgEncodeGencodeEntrezGene
 * from database.  Dispose of this with wgEncodeGencodeEntrezGeneFree(). */

struct wgEncodeGencodeEntrezGene *wgEncodeGencodeEntrezGeneLoadAll(char *fileName);
/* Load all wgEncodeGencodeEntrezGene from whitespace-separated file.
 * Dispose of this with wgEncodeGencodeEntrezGeneFreeList(). */

struct wgEncodeGencodeEntrezGene *wgEncodeGencodeEntrezGeneLoadAllByChar(char *fileName, char chopper);
/* Load all wgEncodeGencodeEntrezGene from chopper separated file.
 * Dispose of this with wgEncodeGencodeEntrezGeneFreeList(). */

#define wgEncodeGencodeEntrezGeneLoadAllByTab(a) wgEncodeGencodeEntrezGeneLoadAllByChar(a, '\t');
/* Load all wgEncodeGencodeEntrezGene from tab separated file.
 * Dispose of this with wgEncodeGencodeEntrezGeneFreeList(). */

struct wgEncodeGencodeEntrezGene *wgEncodeGencodeEntrezGeneCommaIn(char **pS, struct wgEncodeGencodeEntrezGene *ret);
/* Create a wgEncodeGencodeEntrezGene out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new wgEncodeGencodeEntrezGene */

void wgEncodeGencodeEntrezGeneFree(struct wgEncodeGencodeEntrezGene **pEl);
/* Free a single dynamically allocated wgEncodeGencodeEntrezGene such as created
 * with wgEncodeGencodeEntrezGeneLoad(). */

void wgEncodeGencodeEntrezGeneFreeList(struct wgEncodeGencodeEntrezGene **pList);
/* Free a list of dynamically allocated wgEncodeGencodeEntrezGene's */

void wgEncodeGencodeEntrezGeneOutput(struct wgEncodeGencodeEntrezGene *el, FILE *f, char sep, char lastSep);
/* Print out wgEncodeGencodeEntrezGene.  Separate fields with sep. Follow last field with lastSep. */

#define wgEncodeGencodeEntrezGeneTabOut(el,f) wgEncodeGencodeEntrezGeneOutput(el,f,'\t','\n');
/* Print out wgEncodeGencodeEntrezGene as a line in a tab-separated file. */

#define wgEncodeGencodeEntrezGeneCommaOut(el,f) wgEncodeGencodeEntrezGeneOutput(el,f,',',',');
/* Print out wgEncodeGencodeEntrezGene as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* WGENCODEGENCODEENTREZGENE_H */

