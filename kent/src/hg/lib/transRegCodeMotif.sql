# dnaMotif.sql was originally generated by the autoSql program, which also 
# generated dnaMotif.c and dnaMotif.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#A gapless DNA motif
CREATE TABLE transRegCodeMotif (
    name varchar(255) not null,	# Motif name.
    columnCount int not null,	# Count of columns in motif.
    aProb longblob not null,	# Probability of A's in each column.
    cProb longblob not null,	# Probability of C's in each column.
    gProb longblob not null,	# Probability of G's in each column.
    tProb longblob not null,	# Probability of T's in each column.
              #Indices
    PRIMARY KEY(name(32))
);
