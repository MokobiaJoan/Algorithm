# Algorithm
    Implementation of an encoder and decoder of the ascii85

# Author
Мокобиа Джоан Чидиебере, Группа 24.Б83_мм

# Contacts
st135508@student.spbu.ru


To build Task 1.1(Decoder):

BUILD: "make"


RUN PROGRAM: echo -n "input" | ./ascii85 -e
             
             echo -n "-e result" | ./ascii85 -d   
             

RUN TEST(c++): ./test_ascii85

RUN TEST(C++ & PYTHON): make test_all

CLEAN BUILD FILES: make clean