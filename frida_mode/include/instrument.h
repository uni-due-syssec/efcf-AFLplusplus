#ifndef _INSTRUMENT_H
#define _INSTRUMENT_H

#include "frida-gumjs.h"

#include "config.h"

extern char *           instrument_debug_filename;
extern gboolean         instrument_tracing;
extern gboolean         instrument_optimize;
extern gboolean         instrument_unique;
extern __thread guint64 instrument_previous_pc;
extern guint64          instrument_hash_zero;

extern uint8_t *__afl_area_ptr;
extern uint32_t __afl_map_size;

void instrument_config(void);

void instrument_init(void);

GumStalkerTransformer *instrument_get_transformer(void);

/* Functions to be implemented by the different architectures */
gboolean instrument_is_coverage_optimize_supported(void);

void instrument_coverage_optimize(const cs_insn *   instr,
                                  GumStalkerOutput *output);

void     instrument_debug_config(void);
void     instrument_debug_init(void);
void     instrument_debug_start(uint64_t address, GumStalkerOutput *output);
void     instrument_debug_instruction(uint64_t address, uint16_t size);
void     instrument_debug_end(GumStalkerOutput *output);
void     instrument_flush(GumStalkerOutput *output);
gpointer instrument_cur(GumStalkerOutput *output);

void instrument_on_fork();

guint64 instrument_get_offset_hash(GumAddress current_rip);

#endif

