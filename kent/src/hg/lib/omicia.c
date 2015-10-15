/* omicia.c was originally generated by the autoSql program, which also 
 * generated omicia.h and omicia.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "omicia.h"


void omiciaAutoStaticLoad(char **row, struct omiciaAuto *ret)
/* Load a row from omiciaAuto table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->bin = sqlUnsigned(row[0]);
ret->chrom = row[1];
ret->chromStart = sqlUnsigned(row[2]);
ret->chromEnd = sqlUnsigned(row[3]);
ret->name = row[4];
ret->score = sqlUnsigned(row[5]);
safecpy(ret->strand, sizeof(ret->strand), row[6]);
}

struct omiciaAuto *omiciaAutoLoad(char **row)
/* Load a omiciaAuto from row fetched with select * from omiciaAuto
 * from database.  Dispose of this with omiciaAutoFree(). */
{
struct omiciaAuto *ret;

AllocVar(ret);
ret->bin = sqlUnsigned(row[0]);
ret->chrom = cloneString(row[1]);
ret->chromStart = sqlUnsigned(row[2]);
ret->chromEnd = sqlUnsigned(row[3]);
ret->name = cloneString(row[4]);
ret->score = sqlUnsigned(row[5]);
safecpy(ret->strand, sizeof(ret->strand), row[6]);
return ret;
}

struct omiciaAuto *omiciaAutoLoadAll(char *fileName) 
/* Load all omiciaAuto from a whitespace-separated file.
 * Dispose of this with omiciaAutoFreeList(). */
{
struct omiciaAuto *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[7];

while (lineFileRow(lf, row))
    {
    el = omiciaAutoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaAuto *omiciaAutoLoadAllByChar(char *fileName, char chopper) 
/* Load all omiciaAuto from a chopper separated file.
 * Dispose of this with omiciaAutoFreeList(). */
{
struct omiciaAuto *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[7];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = omiciaAutoLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaAuto *omiciaAutoLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all omiciaAuto from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with omiciaAutoFreeList(). */
{
struct omiciaAuto *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = omiciaAutoLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void omiciaAutoSaveToDb(struct sqlConnection *conn, struct omiciaAuto *el, char *tableName, int updateSize)
/* Save omiciaAuto as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( %u,'%s',%u,%u,'%s',%u,'%s')", 
	tableName,  el->bin,  el->chrom,  el->chromStart,  el->chromEnd,  el->name,  el->score,  el->strand);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct omiciaAuto *omiciaAutoCommaIn(char **pS, struct omiciaAuto *ret)
/* Create a omiciaAuto out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new omiciaAuto */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->bin = sqlUnsignedComma(&s);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
*pS = s;
return ret;
}

void omiciaAutoFree(struct omiciaAuto **pEl)
/* Free a single dynamically allocated omiciaAuto such as created
 * with omiciaAutoLoad(). */
{
struct omiciaAuto *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void omiciaAutoFreeList(struct omiciaAuto **pList)
/* Free a list of dynamically allocated omiciaAuto's */
{
struct omiciaAuto *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    omiciaAutoFree(&el);
    }
*pList = NULL;
}

void omiciaAutoOutput(struct omiciaAuto *el, FILE *f, char sep, char lastSep) 
/* Print out omiciaAuto.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->bin);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void omiciaHandStaticLoad(char **row, struct omiciaHand *ret)
/* Load a row from omiciaHand table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->bin = sqlUnsigned(row[0]);
ret->chrom = row[1];
ret->chromStart = sqlUnsigned(row[2]);
ret->chromEnd = sqlUnsigned(row[3]);
ret->name = row[4];
ret->score = sqlUnsigned(row[5]);
safecpy(ret->strand, sizeof(ret->strand), row[6]);
}

struct omiciaHand *omiciaHandLoad(char **row)
/* Load a omiciaHand from row fetched with select * from omiciaHand
 * from database.  Dispose of this with omiciaHandFree(). */
{
struct omiciaHand *ret;

AllocVar(ret);
ret->bin = sqlUnsigned(row[0]);
ret->chrom = cloneString(row[1]);
ret->chromStart = sqlUnsigned(row[2]);
ret->chromEnd = sqlUnsigned(row[3]);
ret->name = cloneString(row[4]);
ret->score = sqlUnsigned(row[5]);
safecpy(ret->strand, sizeof(ret->strand), row[6]);
return ret;
}

struct omiciaHand *omiciaHandLoadAll(char *fileName) 
/* Load all omiciaHand from a whitespace-separated file.
 * Dispose of this with omiciaHandFreeList(). */
{
struct omiciaHand *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[7];

while (lineFileRow(lf, row))
    {
    el = omiciaHandLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaHand *omiciaHandLoadAllByChar(char *fileName, char chopper) 
/* Load all omiciaHand from a chopper separated file.
 * Dispose of this with omiciaHandFreeList(). */
{
struct omiciaHand *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[7];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = omiciaHandLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaHand *omiciaHandLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all omiciaHand from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with omiciaHandFreeList(). */
{
struct omiciaHand *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = omiciaHandLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void omiciaHandSaveToDb(struct sqlConnection *conn, struct omiciaHand *el, char *tableName, int updateSize)
/* Save omiciaHand as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( %u,'%s',%u,%u,'%s',%u,'%s')", 
	tableName,  el->bin,  el->chrom,  el->chromStart,  el->chromEnd,  el->name,  el->score,  el->strand);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct omiciaHand *omiciaHandCommaIn(char **pS, struct omiciaHand *ret)
/* Create a omiciaHand out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new omiciaHand */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->bin = sqlUnsignedComma(&s);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->score = sqlUnsignedComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
*pS = s;
return ret;
}

void omiciaHandFree(struct omiciaHand **pEl)
/* Free a single dynamically allocated omiciaHand such as created
 * with omiciaHandLoad(). */
{
struct omiciaHand *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freez(pEl);
}

void omiciaHandFreeList(struct omiciaHand **pList)
/* Free a list of dynamically allocated omiciaHand's */
{
struct omiciaHand *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    omiciaHandFree(&el);
    }
*pList = NULL;
}

void omiciaHandOutput(struct omiciaHand *el, FILE *f, char sep, char lastSep) 
/* Print out omiciaHand.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->bin);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->chrom);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->chromStart);
fputc(sep,f);
fprintf(f, "%u", el->chromEnd);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
fprintf(f, "%u", el->score);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void omiciaLinkStaticLoad(char **row, struct omiciaLink *ret)
/* Load a row from omiciaLink table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = row[0];
ret->attrType = row[1];
ret->raKey = row[2];
ret->acc = row[3];
ret->displayVal = row[4];
}

struct omiciaLink *omiciaLinkLoad(char **row)
/* Load a omiciaLink from row fetched with select * from omiciaLink
 * from database.  Dispose of this with omiciaLinkFree(). */
{
struct omiciaLink *ret;

AllocVar(ret);
ret->id = cloneString(row[0]);
ret->attrType = cloneString(row[1]);
ret->raKey = cloneString(row[2]);
ret->acc = cloneString(row[3]);
ret->displayVal = cloneString(row[4]);
return ret;
}

struct omiciaLink *omiciaLinkLoadAll(char *fileName) 
/* Load all omiciaLink from a whitespace-separated file.
 * Dispose of this with omiciaLinkFreeList(). */
{
struct omiciaLink *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileRow(lf, row))
    {
    el = omiciaLinkLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaLink *omiciaLinkLoadAllByChar(char *fileName, char chopper) 
/* Load all omiciaLink from a chopper separated file.
 * Dispose of this with omiciaLinkFreeList(). */
{
struct omiciaLink *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[5];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = omiciaLinkLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaLink *omiciaLinkLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all omiciaLink from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with omiciaLinkFreeList(). */
{
struct omiciaLink *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = omiciaLinkLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void omiciaLinkSaveToDb(struct sqlConnection *conn, struct omiciaLink *el, char *tableName, int updateSize)
/* Save omiciaLink as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( '%s','%s','%s','%s','%s')", 
	tableName,  el->id,  el->attrType,  el->raKey,  el->acc,  el->displayVal);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct omiciaLink *omiciaLinkCommaIn(char **pS, struct omiciaLink *ret)
/* Create a omiciaLink out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new omiciaLink */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlStringComma(&s);
ret->attrType = sqlStringComma(&s);
ret->raKey = sqlStringComma(&s);
ret->acc = sqlStringComma(&s);
ret->displayVal = sqlStringComma(&s);
*pS = s;
return ret;
}

void omiciaLinkFree(struct omiciaLink **pEl)
/* Free a single dynamically allocated omiciaLink such as created
 * with omiciaLinkLoad(). */
{
struct omiciaLink *el;

if ((el = *pEl) == NULL) return;
freeMem(el->id);
freeMem(el->attrType);
freeMem(el->raKey);
freeMem(el->acc);
freeMem(el->displayVal);
freez(pEl);
}

void omiciaLinkFreeList(struct omiciaLink **pList)
/* Free a list of dynamically allocated omiciaLink's */
{
struct omiciaLink *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    omiciaLinkFree(&el);
    }
*pList = NULL;
}

void omiciaLinkOutput(struct omiciaLink *el, FILE *f, char sep, char lastSep) 
/* Print out omiciaLink.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->id);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->attrType);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->raKey);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->acc);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->displayVal);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

void omiciaAttrStaticLoad(char **row, struct omiciaAttr *ret)
/* Load a row from omiciaAttr table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = row[0];
ret->attrType = row[1];
ret->attrVal = row[2];
}

struct omiciaAttr *omiciaAttrLoad(char **row)
/* Load a omiciaAttr from row fetched with select * from omiciaAttr
 * from database.  Dispose of this with omiciaAttrFree(). */
{
struct omiciaAttr *ret;

AllocVar(ret);
ret->id = cloneString(row[0]);
ret->attrType = cloneString(row[1]);
ret->attrVal = cloneString(row[2]);
return ret;
}

struct omiciaAttr *omiciaAttrLoadAll(char *fileName) 
/* Load all omiciaAttr from a whitespace-separated file.
 * Dispose of this with omiciaAttrFreeList(). */
{
struct omiciaAttr *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileRow(lf, row))
    {
    el = omiciaAttrLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaAttr *omiciaAttrLoadAllByChar(char *fileName, char chopper) 
/* Load all omiciaAttr from a chopper separated file.
 * Dispose of this with omiciaAttrFreeList(). */
{
struct omiciaAttr *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[3];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = omiciaAttrLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct omiciaAttr *omiciaAttrLoadByQuery(struct sqlConnection *conn, char *query)
/* Load all omiciaAttr from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with omiciaAttrFreeList(). */
{
struct omiciaAttr *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = omiciaAttrLoad(row);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void omiciaAttrSaveToDb(struct sqlConnection *conn, struct omiciaAttr *el, char *tableName, int updateSize)
/* Save omiciaAttr as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( '%s','%s','%s')", 
	tableName,  el->id,  el->attrType,  el->attrVal);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct omiciaAttr *omiciaAttrCommaIn(char **pS, struct omiciaAttr *ret)
/* Create a omiciaAttr out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new omiciaAttr */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlStringComma(&s);
ret->attrType = sqlStringComma(&s);
ret->attrVal = sqlStringComma(&s);
*pS = s;
return ret;
}

void omiciaAttrFree(struct omiciaAttr **pEl)
/* Free a single dynamically allocated omiciaAttr such as created
 * with omiciaAttrLoad(). */
{
struct omiciaAttr *el;

if ((el = *pEl) == NULL) return;
freeMem(el->id);
freeMem(el->attrType);
freeMem(el->attrVal);
freez(pEl);
}

void omiciaAttrFreeList(struct omiciaAttr **pList)
/* Free a list of dynamically allocated omiciaAttr's */
{
struct omiciaAttr *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    omiciaAttrFree(&el);
    }
*pList = NULL;
}

void omiciaAttrOutput(struct omiciaAttr *el, FILE *f, char sep, char lastSep) 
/* Print out omiciaAttr.  Separate fields with sep. Follow last field with lastSep. */
{
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->id);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->attrType);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->attrVal);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

