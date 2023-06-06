CREATE TABLE IF NOT EXISTS quiz(
    id INTEGER NOT NULL AUTO_INCREMENT;
description TEXT
);
CREATE Table IF NOT EXISTS Questions (
    id INTEGER NOT NULL AUTO_INCREMENT;
TEXT lib
);
CREATE TABLE if NOT EXISTS answer (
    id INTEGER NOT NULL AUTO_INCREMENT;
TEXT lib
);
CREATE TABLE IF NOT EXISTS ans (
    id INTEGER NOT NULL AUTO_INCREMENT;
questionid int;
answerid int;
Foreign Key (questionid) REFERENCES question(id);
Foreign Key (answerid) REFERENCES answer(id)
);