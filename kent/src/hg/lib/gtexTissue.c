/* gtexTissue.c was originally generated by the autoSql program, which also 
 * generated gtexTissue.h and gtexTissue.sql.  This module links the database and
 * the RAM representation of objects. */

#include "common.h"
#include "linefile.h"
#include "dystring.h"
#include "jksql.h"
#include "gtexTissue.h"



char *gtexTissueCommaSepFieldNames = "id,name,description,organ";

void gtexTissueStaticLoad(char **row, struct gtexTissue *ret)
/* Load a row from gtexTissue table into ret.  The contents of ret will
 * be replaced at the next call to this function. */
{

ret->id = sqlUnsigned(row[0]);
ret->name = row[1];
ret->description = row[2];
ret->organ = row[3];
}

struct gtexTissue *gtexTissueLoad(char **row)
/* Load a gtexTissue from row fetched with select * from gtexTissue
 * from database.  Dispose of this with gtexTissueFree(). */
{
struct gtexTissue *ret;

AllocVar(ret);
ret->id = sqlUnsigned(row[0]);
ret->name = cloneString(row[1]);
ret->description = cloneString(row[2]);
ret->organ = cloneString(row[3]);
return ret;
}

struct gtexTissue *gtexTissueLoadAll(char *fileName) 
/* Load all gtexTissue from a whitespace-separated file.
 * Dispose of this with gtexTissueFreeList(). */
{
struct gtexTissue *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileRow(lf, row))
    {
    el = gtexTissueLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gtexTissue *gtexTissueLoadAllByChar(char *fileName, char chopper) 
/* Load all gtexTissue from a chopper separated file.
 * Dispose of this with gtexTissueFreeList(). */
{
struct gtexTissue *list = NULL, *el;
struct lineFile *lf = lineFileOpen(fileName, TRUE);
char *row[4];

while (lineFileNextCharRow(lf, chopper, row, ArraySize(row)))
    {
    el = gtexTissueLoad(row);
    slAddHead(&list, el);
    }
lineFileClose(&lf);
slReverse(&list);
return list;
}

struct gtexTissue *gtexTissueCommaIn(char **pS, struct gtexTissue *ret)
/* Create a gtexTissue out of a comma separated string. 
 * This will fill in ret if non-null, otherwise will
 * return a new gtexTissue */
{
char *s = *pS;

if (ret == NULL)
    AllocVar(ret);
ret->id = sqlUnsignedComma(&s);
ret->name = sqlStringComma(&s);
ret->description = sqlStringComma(&s);
ret->organ = sqlStringComma(&s);
*pS = s;
return ret;
}

void gtexTissueFree(struct gtexTissue **pEl)
/* Free a single dynamically allocated gtexTissue such as created
 * with gtexTissueLoad(). */
{
struct gtexTissue *el;

if ((el = *pEl) == NULL) return;
freeMem(el->name);
freeMem(el->description);
freeMem(el->organ);
freez(pEl);
}

void gtexTissueFreeList(struct gtexTissue **pList)
/* Free a list of dynamically allocated gtexTissue's */
{
struct gtexTissue *el, *next;

for (el = *pList; el != NULL; el = next)
    {
    next = el->next;
    gtexTissueFree(&el);
    }
*pList = NULL;
}

void gtexTissueOutput(struct gtexTissue *el, FILE *f, char sep, char lastSep) 
/* Print out gtexTissue.  Separate fields with sep. Follow last field with lastSep. */
{
fprintf(f, "%u", el->id);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->name);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->description);
if (sep == ',') fputc('"',f);
fputc(sep,f);
if (sep == ',') fputc('"',f);
fprintf(f, "%s", el->organ);
if (sep == ',') fputc('"',f);
fputc(lastSep,f);
}

/* -------------------------------- End autoSql Generated Code -------------------------------- */

void gtexTissueCreateTable(struct sqlConnection *conn, char *table)
/* Create expression record format table of given name. */
{
char query[1024];

sqlSafef(query, sizeof(query),
"CREATE TABLE %s (\n"
"    id int unsigned not null,	# internal id\n"
"    name varchar(255) not null,       # short UCSC identifier\n"
"    description varchar(255) not null, # GTEx tissue type detail\n"
"    organ varchar(255) not null,      # GTEx tissue collection area\n"
"              #Indices\n"
"    PRIMARY KEY(id)\n"
")\n",   table);
sqlRemakeTable(conn, table, query);
}
