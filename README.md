Compile with:
```
g++-13 -std=c++23 -Wall -Wextra -g -ggdb -O3 median\_benchmark.cc
```

Extract results with:
```
awk -f collate.awk -vC=<col>
```
where `<col>` is the column number (3, 4 or 5) for the three algoriths under
test. 
