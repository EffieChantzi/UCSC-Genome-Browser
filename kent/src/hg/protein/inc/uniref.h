/* uniref.h was originally generated by the autoSql program, which also 
 * generated uniref.c and uniref.sql.  This header links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2005 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#ifndef UNIREF_H
#define UNIREF_H

#define UNIREF_NUM_COLS 7

struct uniref
/* parse for a tab separate version of the uniref information */
    {
    struct uniref *next;  /* Next in singly linked list. */
    char entryId[33];	/* uniref entry id */
    char type[5];	/* rep or mem */
    char upId[17];	/* uniprot id */
    char upAcc[17];	/* uniprot accession */
    char *org;	/* organism */
    int tax;	/* taxonomy id */
    int len;	/* protein length */
    };

void unirefStaticLoad(char **row, struct uniref *ret);
/* Load a row from uniref table into ret.  The contents of ret will
 * be replaced at the next call to this function. */

struct uniref *unirefLoad(char **row);
/* Load a uniref from row fetched with select * from uniref
 * from database.  Dispose of this with unirefFree(). */

struct uniref *unirefLoadAll(char *fileName);
/* Load all uniref from whitespace-separated file.
 * Dispose of this with unirefFreeList(). */

struct uniref *unirefLoadAllByChar(char *fileName, char chopper);
/* Load all uniref from chopper separated file.
 * Dispose of this with unirefFreeList(). */

#define unirefLoadAllByTab(a) unirefLoadAllByChar(a, '\t');
/* Load all uniref from tab separated file.
 * Dispose of this with unirefFreeList(). */

struct uniref *unirefCommaIn(char **pS, struct uniref *ret);
/* Create a uniref out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new uniref */

void unirefFree(struct uniref **pEl);
/* Free a single dynamically allocated uniref such as created
 * with unirefLoad(). */

void unirefFreeList(struct uniref **pList);
/* Free a list of dynamically allocated uniref's */

void unirefOutput(struct uniref *el, FILE *f, char sep, char lastSep);
/* Print out uniref.  Separate fields with sep. Follow last field with lastSep. */

#define unirefTabOut(el,f) unirefOutput(el,f,'\t','\n');
/* Print out uniref as a line in a tab-separated file. */

#define unirefCommaOut(el,f) unirefOutput(el,f,',',',');
/* Print out uniref as a comma separated list including final comma. */

/* -------------------------------- End autoSql Generated Code -------------------------------- */

#endif /* UNIREF_H */

