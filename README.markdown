
This little benchmark demonstrates performance of resizing vector vs list traversal.
The task is insert elements to container in a way to keep it sorted after each insertions.
There are three competitors: list, vector and set.
It may be not obvious, but vector performs much better in comparison to list. Moreover, it
is faster on typical desktop machine then set up to 4096 integer insertions, then set beats vector.

My results (Mac Mini Late 2012, i7):

     1,16: vector elapsed microseconds: 17
     1,16: list elapsed microseconds: 2
     1,16: set elapsed microseconds: 3

     2,32: vector elapsed microseconds: 2
     2,32: list elapsed microseconds: 7
     2,32: set elapsed microseconds: 4

     3,64: vector elapsed microseconds: 4
     3,64: list elapsed microseconds: 12
     3,64: set elapsed microseconds: 8

     4,128: vector elapsed microseconds: 8
     4,128: list elapsed microseconds: 33
     4,128: set elapsed microseconds: 18

     5,256: vector elapsed microseconds: 18
     5,256: list elapsed microseconds: 107
     5,256: set elapsed microseconds: 38

     6,512: vector elapsed microseconds: 42
     6,512: list elapsed microseconds: 400
     6,512: set elapsed microseconds: 94

     7,1024: vector elapsed microseconds: 106
     7,1024: list elapsed microseconds: 1463
     7,1024: set elapsed microseconds: 154

     8,2048: vector elapsed microseconds: 259
     8,2048: list elapsed microseconds: 9091
     8,2048: set elapsed microseconds: 328

     9,4096: vector elapsed microseconds: 708
     9,4096: list elapsed microseconds: 52221
     9,4096: set elapsed microseconds: 631

     10,8192: vector elapsed microseconds: 2381
     10,8192: list elapsed microseconds: 245066
     10,8192: set elapsed microseconds: 1257
     