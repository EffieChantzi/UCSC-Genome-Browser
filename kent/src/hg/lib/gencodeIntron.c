/* gencodeIntron.c was originally generated by the autoSql program, which also 
 * generated gencodeIntron.h and gencodeIntron.sql.  This module links the database and
 * the RAM representation of objects. */

/* Copyright (C) 2014 The Regents of the University of California 
 * See README in this or parent directory for licensing information. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "gencodeIntron.h"


void gencodeIntronStaticLoad(char **row, struct gencodeIntron *ret)
/* Load a row from gencodeIntron table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->chrom = row[0];
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = row[3];
ret->status = row[4];
strcpy(ret->strand, row[5]);
ret->transcript = row[6];
ret->geneId = row[7];
}

struct gencodeIntron *gencodeIntronLoad(char **row)
/* Load a gencodeIntron from row fetched with select * from gencodeIntron
 * from database.  Dispose of this with gencodeIntronFree(). */
{
struct gencodeIntron *ret;

AllocVar(ret);
ret->chrom = cloneString(row[0]);
ret->chromStart = sqlUnsigned(row[1]);
ret->chromEnd = sqlUnsigned(row[2]);
ret->name = cloneString(row[3]);
ret->status = cloneString(row[4]);
strcpy(ret->strand, row[5]);
ret->transcript = cloneString(row[6]);
ret->geneId = cloneString(row[7]);
return ret;
}

struct gencodeIntron *gencodeIntronLoadAll(char *fileName) 
/* Load all gencodeIntron from a whitespace-separated file.
 * Dispose of this with gencodeIntronFreeList(). */
{
struct gencodeIntron *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[8];

while (lineFileRow(lf, row))
    {
    el = gencodeIntronLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gencodeIntron *gencodeIntronLoadAllByChar(char *fileName, char chopper) 
/* Load all gencodeIntron from a chopper separated file.
 * Dispose of this with gencodeIntronFreeList(). */
{
struct gencodeIntron *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[8];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = gencodeIntronLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gencodeIntron *gencodeIntronLoadByQuery(struct sqlConnection *conn, char *query, int rowOffset)
/* Load all gencodeIntron from table that satisfy the query given.  
 * Where query is of the form 'select * from example where something=something'
 * or 'select example.* from example, anotherTable where example.something = 
 * anotherTable.something'.
 * Dispose of this with gencodeIntronFreeList(). */
{
struct gencodeIntron *list = NULL, *el;
struct sqlResult *sr;
char **row;

sr = sqlGetResult(conn, query);
while ((row = sqlNextRow(sr)) != NULL)
    {
    el = gencodeIntronLoad(row+rowOffset);
    slAddHead(&list, el);
    }
slReverse(&list);
sqlFreeResult(&sr);
return list;
}

void gencodeIntronSaveToDb(struct sqlConnection *conn, struct gencodeIntron *el, char *tableName, int updateSize)
/* Save gencodeIntron as a row to the table specified by tableName. 
 * As blob fields may be arbitrary size updateSize specifies the approx size
 * of a string that would contain the entire query. Arrays of native types are
 * converted to comma separated strings and loaded as such, User defined types are
 * inserted as NULL. Strings are automatically escaped to allow insertion into the database. */
{
struct dyString *update = newDyString(updateSize);
sqlDyStringPrintf(update, "insert into %s values ( '%s',%u,%u,'%s','%s','%s','%s','%s')", 
	tableName,  el->chrom,  el->chromStart,  el->chromEnd,  el->name,  el->status,  el->strand,  el->transcript,  el->geneId);
sqlUpdate(conn, update->string);
freeDyString(&update);
}


struct gencodeIntron *gencodeIntronCommaIn(char **pS, struct gencodeIntron *ret)
/* Create a gencodeIntron out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gencodeIntron */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->chrom = sqlStringComma(&s);
ret->chromStart = sqlUnsignedComma(&s);
ret->chromEnd = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->status = sqlStringComma(&s);
sqlFixedStringComma(&s, ret->strand, sizeof(ret->strand));
ret->transcript = sqlStringComma(&s);
ret->geneId = sqlStringComma(&s);
*pS = s;
return ret;
}

void gencodeIntronFree(struct gencodeIntron **pEl)
/* Free a single dynamically allocated gencodeIntron such as created
 * with gencodeIntronLoad(). */
{
struct gencodeIntron *el;

if ((el = *pEl) == NULL) return;
freeMem(el->chrom);
freeMem(el->name);
freeMem(el->status);
freeMem(el->transcript);
freeMem(el->geneId);
freez(pEl);
}

void gencodeIntronFreeList(struct gencodeIntron **pList)
/* Free a list of dynamically allocated gencodeIntron's */
{
struct gencodeIntron *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    gencodeIntronFree(&el);
    }
*pList = NULL;
}

void gencodeIntronOutput(struct gencodeIntron *el, FILE *f, char sep, char lastSep) 
/* Print out gencodeIntron.  Separate fields with sep. Follow last field with lastSep. */
{
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
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->status);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->strand);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->transcript);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->geneId);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

void gencodeIntronTableCreate(struct sqlConnection *conn, char *tableName, int indexSize)
/* Create a gencodeIntron table with the given name */
{
char *createString =
"CREATE TABLE %s (\n"
"       chrom varchar(255) not null,	# Chromosome\n"
"       chromStart int unsigned not null,	# Start position in chromosome\n"
"       chromEnd int unsigned not null,	# End position in chromosome\n"
"       name varchar(255) not null,	# Intron ID\n"
"       status enum('not_tested', 'RT_positive','RT_negative','RT_wrong_junction','RT_submitted', 'RACE_validated'),      # Status\n"
"       strand char(1) not null,	# + or -\n"
"       transcript varchar(255) not null,	# Transcript ID from GTF\n"
"       geneId varchar(255) not null,	# Gene ID from GTF\n"
"    INDEX(chrom(%d),chromStart),\n"
"    INDEX(chrom(%d),chromEnd)\n"
")\n";
struct dyString *dy = newDyString(1024);
sqlDyStringPrintf(dy, createString, tableName, indexSize, indexSize, indexSize);
sqlRemakeTable(conn, tableName, dy->string);
dyStringFree(&dy);
}

