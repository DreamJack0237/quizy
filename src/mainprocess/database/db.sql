CREATE TABLE IF NOT EXISTS quiz(
    name varchar(100) UNIQUE,
    id INTEGER PRIMARY KEY AUTOINCREMENT
);
CREATE Table IF NOT EXISTS question (lib TEXT);
CREATE TABLE if NOT EXISTS answer (id INTEGER PRIMARY KEY, TEXT lib);
CREATE TABLE IF NOT EXISTS ans (
    id INTEGER PRIMARY KEY,
    questionid int,
    answerid int,
    Foreign Key (questionid) REFERENCES question(id),
    Foreign Key (answerid) REFERENCES answer(id)
);