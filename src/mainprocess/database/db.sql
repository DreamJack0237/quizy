CREATE TABLE IF NOT EXISTS quiz(
    name varchar(100) UNIQUE,
    id INTEGER PRIMARY KEY AUTOINCREMENT
);
CREATE Table IF NOT EXISTS question (
    lib TEXT,
    quizid INTEGER,
    Foreign Key (quizid) REFERENCES quiz(id)
);
CREATE TABLE if NOT EXISTS answer (
    id INTEGER PRIMARY KEY,
    questionid int,
    lib TEXT,
    correct BOOLEAN default false,
    Foreign Key (questionid) REFERENCES question(id)
);