#ifndef TEXT_H
#define TEXT_H

typedef struct {
    size_t size;
    char text[];
} PgfText;

/* Case sensitive comparison */
PGF_INTERNAL_DECL
int textcmp(PgfText *t1, PgfText *t2);

/* The same as textcmp but returns 0 if t1 is a prefix of t2. */
PGF_INTERNAL_DECL
int textcmp_prefix(PgfText *t1, PgfText *t2);

/* Performs both case-insensitive and case-sensitive comparison. 
 * The first element in res contains the result from
 * the case-insensitive comparison. The second the result 
 * from case-sensitive one. Usually res must be initialized 
 * with {0,0}. If it is not then that can be used
 * to chain a list of comparisons.*/
PGF_INTERNAL_DECL
void texticmp(PgfText *t1, PgfText *t2, int res[2]);

PGF_INTERNAL_DECL
bool textstarts(PgfText *t, PgfText *prefix);

PGF_INTERNAL_DECL
bool textistarts(PgfText *t, PgfText *prefix);

PGF_INTERNAL_DECL
PgfText* string2text(const char *s);

PGF_INTERNAL_DECL
PgfText* textdup(PgfText *t1);

PGF_INTERNAL_DECL
ref<PgfText> textdup_db(PgfText *t1);

PGF_INTERNAL_DECL
ref<PgfText> textdup_db(ref<PgfText> t1);

PGF_INTERNAL_DECL
void text_db_release(ref<PgfText> text);

PGF_INTERNAL_DECL uint32_t
pgf_utf8_decode(const uint8_t** src_inout);

PGF_INTERNAL_DECL void
pgf_utf8_encode(uint32_t ucs, uint8_t** buf);

PGF_INTERNAL_DECL
uint32_t pgf_utf8_to_upper(uint32_t c);

PGF_INTERNAL_DECL
bool pgf_utf8_is_space(uint32_t c);

PGF_INTERNAL_DECL
bool pgf_utf8_is_digit(uint32_t c);

#endif
