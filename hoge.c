#define HOGE

#if defined(HOGE)

int hoge;
#elif defined(FUGA)
int fuga;

#elif 1

bool te = true;

#else
int par;
#if(1)
int Hoge;
#endif

#endif