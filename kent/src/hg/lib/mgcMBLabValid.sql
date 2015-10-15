# mgcMBLabValid.sql was originally generated by the autoSql program, which also 
# generated mgcMBLabValid.c and mgcMBLabValid.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Genbank accessions of MGC clones that are in the Brent Lab validation database
CREATE TABLE mgcMBLabValid (
    acc char(8) not null,	# Genbank accession
              #Indices
    PRIMARY KEY(acc)
);
