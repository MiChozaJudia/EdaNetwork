#ifndef PARSER_H
#define PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef int (*pCallback) (char *, char *, void *);
    
    int parseCmdLine (int argc, char *argv[], pCallback p, void *userData);
#define SYNTAX_ERROR -1
#define CALL_ERROR -2



#ifdef __cplusplus
}
#endif

#endif /* PARSER_H */

