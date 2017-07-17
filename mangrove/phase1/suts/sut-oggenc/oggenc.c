#include <alloca.h>
#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
struct option
{
  const char *name;
  int has_arg;
  int *flag;
  int val;
};
# define no_argument            0
# define required_argument      1
# define optional_argument      2
;
;
;
extern int _getopt_internal (int ___argc, char *const *___argv,
                             const char *__shortopts,
                             const struct option *__longopts, int *__longind,
                             int __long_only);
#define setbinmode(x) {}
#define DEFAULT_NAMEFMT_REMOVE "/"
#define DEFAULT_NAMEFMT_REPLACE NULL
#define __ENCODE_H
#define _vorbis_codec_h_
#define _OGG_H
#define _OS_TYPES_H
#define _ogg_malloc  malloc
#define _ogg_calloc  calloc
#define _ogg_realloc realloc
#define _ogg_free    free
#define __CONFIG_TYPES_H__
typedef int16_t ogg_int16_t;
typedef u_int16_t ogg_uint16_t;
typedef int32_t ogg_int32_t;
typedef u_int32_t ogg_uint32_t;
typedef int64_t ogg_int64_t;
typedef struct {
} oggpack_buffer;
typedef struct {
} ogg_page;
typedef struct {
} ogg_stream_state;
typedef struct {
} ogg_packet;
typedef struct {
} ogg_sync_state;
typedef struct vorbis_info{
} vorbis_info;
typedef struct vorbis_dsp_state{
} vorbis_dsp_state;
typedef struct vorbis_block{
} vorbis_block;
struct alloc_chain{
};
typedef struct vorbis_comment{
} vorbis_comment;
#define OV_FALSE      -1  
#define OV_EOF        -2
#define OV_HOLE       -3
#define OV_EREAD      -128
#define OV_EFAULT     -129
#define OV_EIMPL      -130
#define OV_EINVAL     -131
#define OV_ENOTVORBIS -132
#define OV_EBADHEADER -133
#define OV_EVERSION   -134
#define OV_ENOTAUDIO  -135
#define OV_EBADPACKET -136
#define OV_EBADLINK   -137
#define OV_ENOSEEK    -138
typedef void TIMER;
typedef long (*audio_read_func)(void *src, float **buffer, int samples);
typedef void (*progress_func)(char *fn, long totalsamples, 
		long samples, double time);
typedef void (*enc_end_func)(char *fn, double time, int rate, 
		long samples, long bytes);
typedef void (*enc_start_func)(char *fn, char *outfn, int bitrate, 
        float quality, int qset, int managed, int min_br, int max_br);
typedef void (*error_func)(char *errormessage);
typedef struct {
} adv_opt;
typedef struct
{
} oe_options;
typedef struct
{
} oe_enc_opt;
#define __AUDIO_H
typedef struct
{
} input_format;
typedef struct {
} wav_fmt;
typedef struct {
} wavfile;
typedef struct {
} aiff_fmt;
typedef wavfile aifffile; 
#define _(X) (X)
#define textdomain(X)
#define bindtextdomain(X, Y)
#define N_(X) (X)
#define VERSION_STRING "OggEnc v1.0.1 (libvorbis 1.0.1)\n"
#define COPYRIGHT "(c) 2000-2003 Michael Smith <msmith@xiph.org>\n"
#define CHUNK 4096 
int main(int argc, char **argv)
;
#define _RESAMPLE_H_INCLUDED
typedef float SAMPLE;
typedef struct
{
} res_state;
typedef enum
{
	RES_END,
} res_parameter;
#define WAV_HEADER_SIZE 44
#define READ_U32_LE(buf) \
	(((buf)[3]<<24)|((buf)[2]<<16)|((buf)[1]<<8)|((buf)[0]&0xff))
#define READ_U16_LE(buf) \
	(((buf)[1]<<8)|((buf)[0]&0xff))
#define READ_U32_BE(buf) \
	(((buf)[0]<<24)|((buf)[1]<<16)|((buf)[2]<<8)|((buf)[3]&0xff))
#define READ_U16_BE(buf) \
	(((buf)[0]<<8)|((buf)[1]&0xff))
typedef struct {
} resampler;
typedef struct {
} scaler;
typedef struct {
} downmix;
#define _OV_ENC_H_
#define OV_ECTL_RATEMANAGE_GET       0x10
#define OV_ECTL_RATEMANAGE_SET       0x11
#define OV_ECTL_RATEMANAGE_AVG       0x12
#define OV_ECTL_RATEMANAGE_HARD      0x13
#define OV_ECTL_LOWPASS_GET          0x20
#define OV_ECTL_LOWPASS_SET          0x21
#define OV_ECTL_IBLOCK_GET           0x30
#define OV_ECTL_IBLOCK_SET           0x31
struct ovectl_ratemanage_arg {
};
#define READSIZE 1024
#define SETD(toset) \
    do {\
        if(sscanf(opts[i].val, "%lf", &dval) != 1)\
            fprintf(stderr, "For option %s, couldn't read value %s as double\n",\
                    opts[i].arg, opts[i].val);\
        else\
            toset = dval;\
    } while(0)
#define SETL(toset) \
    do {\
        if(sscanf(opts[i].val, "%ld", &lval) != 1)\
            fprintf(stderr, "For option %s, couldn't read value %s as integer\n",\
                    opts[i].arg, opts[i].val);\
        else\
            toset = lval;\
    } while(0)
#if defined(__WATCOMC__) || defined(__BORLANDC__)
void setbinmode(FILE *f)
{
	setmode(fileno(f), O_BINARY);
}
#endif
#define PATH_SEPS "/"
#define M_PI       3.14159265358979323846 
char *optarg,  *nextchar,  *posixly_correct;
int optind = 1,  __getopt_initialized,  opterr = 1,  optopt = '?',  first_nonopt,  last_nonopt;
static enum
{
  REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
} ordering;
# define my_index	strchr
# define SWAP_FLAGS(ch1, ch2)
static void exchange (char **);
static void
exchange (argv)
     char **argv;
{
  int bottom = first_nonopt,  middle = last_nonopt,  top = optind;
  char *tem;
  while (top > middle && middle > bottom)
    {
      if (top - middle > middle - bottom)
	{
	  int len = middle - bottom,  i;
	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[top - (middle - bottom) + i];
	      argv[top - (middle - bottom) + i] = tem;
	      SWAP_FLAGS (bottom + i, top - (middle - bottom) + i);
	    }
	  top -= len;
	}
      else
	{
	  int len = top - middle,  i;
	  for (i = 0; i < len; i++)
	    {
	      tem = argv[bottom + i];
	      argv[bottom + i] = argv[middle + i];
	      argv[middle + i] = tem;
	      SWAP_FLAGS (bottom + i, middle + i);
	    }
	  bottom += len;
	}
    }
  first_nonopt += (optind - last_nonopt);
  last_nonopt = optind;
}
static const char *_getopt_initialize (int, char *const *, const char *);
static const char *
_getopt_initialize (argc, argv, optstring)
     int argc;
     char *const *argv;
     const char *optstring;
{
  first_nonopt = last_nonopt = optind;
  nextchar = NULL;
  posixly_correct = getenv ("POSIXLY_CORRECT");
  if (optstring[0] == '-')
    {
      ordering = RETURN_IN_ORDER;
      ++optstring;
    }
  else if (optstring[0] == '+')
    {
      ordering = REQUIRE_ORDER;
      ++optstring;
    }
  else if (posixly_correct != NULL)
    ordering = REQUIRE_ORDER;
  else
    ordering = PERMUTE;
  return optstring;
}
int
_getopt_internal (argc, argv, optstring, longopts, longind, long_only)
     int argc;
     char *const *argv;
     const char *optstring;
     const struct option *longopts;
     int *longind;
     int long_only;
{
  optarg = NULL;
  if (optind == 0 || !__getopt_initialized)
    {
      if (optind == 0)
	optind = 1;	
      optstring = _getopt_initialize (argc, argv, optstring);
      __getopt_initialized = 1;
    }
# define NONOPTION_P (argv[optind][0] != '-' || argv[optind][1] == '\0')
  if (nextchar == NULL || *nextchar == '\0')
    {
      if (last_nonopt > optind)
	last_nonopt = optind;
      if (first_nonopt > optind)
	first_nonopt = optind;
      if (ordering == PERMUTE)
	{
	  if (first_nonopt != last_nonopt && last_nonopt != optind)
	    exchange ((char **) argv);
	  else if (last_nonopt != optind)
	    first_nonopt = optind;
	  while (optind < argc && NONOPTION_P)
	    optind++;
	  last_nonopt = optind;
	}
      if (optind != argc && !strcmp (argv[optind], "--"))
	{
	  optind++;
	  if (first_nonopt != last_nonopt && last_nonopt != optind)
	    exchange ((char **) argv);
	  else if (first_nonopt == last_nonopt)
	    first_nonopt = optind;
	  last_nonopt = argc;
	  optind = argc;
	}
      if (optind == argc)
	{
	  if (first_nonopt != last_nonopt)
	    optind = first_nonopt;
	  return -1;
	}
      if (NONOPTION_P)
	{
	  if (ordering == REQUIRE_ORDER)
	    return -1;
	  optarg = argv[optind++];
	  return 1;
	}
      nextchar = (argv[optind] + 1
		  + (longopts != NULL && argv[optind][1] == '-'));
    }
  if (longopts != NULL
      && (argv[optind][1] == '-'
	  || (long_only && (argv[optind][2] || !my_index (optstring, argv[optind][1])))))
    {
      char *nameend;
      const struct option *p;
      const struct option *pfound = NULL;
      int exact = 0;
      int ambig = 0;
      int indfound = -1;
      int option_index;
      for (nameend = nextchar; *nameend && *nameend != '='; nameend++)
	 ;
      for (p = longopts, option_index = 0; p->name; p++, option_index++)
	if (!strncmp (p->name, nextchar, nameend - nextchar))
	  {
	    if ((unsigned int) (nameend - nextchar)
		== (unsigned int) strlen (p->name))
	      {
		pfound = p;
		indfound = option_index;
		exact = 1;
		break;
	      }
	    else if (pfound == NULL)
	      {
		pfound = p;
		indfound = option_index;
	      }
	    else
	      ambig = 1;
	  }
      if (ambig && !exact)
	{
	  if (opterr)
	    fprintf (stderr, _("%s: option `%s' is ambiguous\n"),
		     argv[0], argv[optind]);
	  nextchar += strlen (nextchar);
	  optind++;
	  optopt = 0;
	  return '?';
	}
      if (pfound != NULL)
	{
	  option_index = indfound;
	  optind++;
	  if (*nameend)
	    {
	      if (pfound->has_arg)
		optarg = nameend + 1;
	      else
		{
		  if (opterr)
		    {
		      if (argv[optind - 1][1] == '-')
			fprintf (stderr,
				 _("%s: option `--%s' doesn't allow an argument\n"),
				 argv[0], pfound->name);
		      else
			fprintf (stderr,
				 _("%s: option `%c%s' doesn't allow an argument\n"),
				 argv[0], argv[optind - 1][0], pfound->name);
		    }
		  nextchar += strlen (nextchar);
		  optopt = pfound->val;
		  return '?';
		}
	    }
	  else if (pfound->has_arg == 1)
	    {
	      if (optind < argc)
		optarg = argv[optind++];
	      else
		{
		  if (opterr)
		    fprintf (stderr,
			   _("%s: option `%s' requires an argument\n"),
			   argv[0], argv[optind - 1]);
		  nextchar += strlen (nextchar);
		  optopt = pfound->val;
		  return optstring[0] == ':' ? ':' : '?';
		}
	    }
	  nextchar += strlen (nextchar);
	  if (longind != NULL)
	    *longind = option_index;
	  if (pfound->flag)
	    {
	      *(pfound->flag) = pfound->val;
	      return 0;
	    }
	  return pfound->val;
	}
      if (!long_only || argv[optind][1] == '-'
	  || my_index (optstring, *nextchar) == NULL)
	{
	  if (opterr)
	    {
	      if (argv[optind][1] == '-')
		fprintf (stderr, _("%s: unrecognized option `--%s'\n"),
			 argv[0], nextchar);
	      else
		fprintf (stderr, _("%s: unrecognized option `%c%s'\n"),
			 argv[0], argv[optind][0], nextchar);
	    }
	  nextchar = (char *) "";
	  optind++;
	  optopt = 0;
	  return '?';
	}
    }
  {
    char c = *nextchar++;
    char *temp = my_index (optstring, c);
    if (*nextchar == '\0')
      ++optind;
    if (temp == NULL || c == ':')
      {
	if (opterr)
	  {
	    if (posixly_correct)
	      fprintf (stderr, _("%s: illegal option -- %c\n"),
		       argv[0], c);
	    else
	      fprintf (stderr, _("%s: invalid option -- %c\n"),
		       argv[0], c);
	  }
	optopt = c;
	return '?';
      }
    if (temp[0] == 'W' && temp[1] == ';')
      {
	char *nameend;
	const struct option *p,  *pfound = NULL;
	int exact = 0,  ambig = 0,  indfound = 0,  option_index;
	if (*nextchar != '\0')
	  {
	    optarg = nextchar;
	    optind++;
	  }
	else if (optind == argc)
	  {
	    if (opterr)
	      {
		fprintf (stderr, _("%s: option requires an argument -- %c\n"),
			 argv[0], c);
	      }
	    optopt = c;
	    if (optstring[0] == ':')
	      c = ':';
	    else
	      c = '?';
	    return c;
	  }
	else
	  optarg = argv[optind++];
	for (nextchar = nameend = optarg; *nameend && *nameend != '='; nameend++)
	   ;
	for (p = longopts, option_index = 0; p->name; p++, option_index++)
	 ;
      }
    return c;
  }
}
#define _V_CODECI_H_
#define _V_ENVELOPE_
#define _OGG_mdct_H_
#define DATA_TYPE float
#define REG_TYPE  float
#define cPI3_8 .38268343236508977175F
#define cPI2_8 .70710678118654752441F
#define cPI1_8 .92387953251128675613F
#define FLOAT_CONV(x) (x)
#define MULT_NORM(x) (x)
#define HALVE(x) ((x)*.5f)
typedef struct {
  DATA_TYPE *trig;
  int       *bitrev;
  DATA_TYPE scale;
} mdct_lookup;
#define VE_PRE    16
#define VE_WIN    4
#define VE_POST   2
#define VE_AMP    (VE_PRE+VE_POST-1)
#define VE_BANDS  7
#define VE_NEARDC 15
#define VE_MINSTRETCH 2   
#define VE_MAXSTRETCH 12  
typedef struct {
  float ampbuf[VE_AMP];
  int   ampptr;
  float nearDC[VE_NEARDC];
  float nearDC_acc;
  float nearDC_partialacc;
  int   nearptr;
} envelope_filter_state;
typedef struct {
  int begin;
  int end;
  float *window;
  float total;
} envelope_band;
typedef struct {
  int ch;
  int winlength;
  int searchstep;
  float minenergy;
  mdct_lookup  mdct;
  float       *mdct_win;
  envelope_band          band[VE_BANDS];
  envelope_filter_state *filter;
  int   stretch;
  int                   *mark;
  long storage;
  long current;
  long curmark;
  long cursor;
} envelope_lookup;
#define _V_CODEBOOK_H_
typedef struct static_codebook{
  long   dim;            
  long   entries;        
  long  *lengthlist;     
  int    maptype;        
  long     q_min;       
  long     q_delta;     
  int      q_quant;     
  int      q_sequencep; 
  long     *quantlist;  
  struct encode_aux_nearestmatch *nearest_tree;
  struct encode_aux_threshmatch  *thresh_tree;
  struct encode_aux_pigeonhole  *pigeon_tree;
  int allocedp;
} static_codebook;
typedef struct encode_aux_nearestmatch{
  long   *ptr0;
  long   *ptr1;
  long   *p;         
  long   *q;         
  long   aux;        
  long   alloc;       
} encode_aux_nearestmatch;
typedef struct encode_aux_threshmatch{
  float *quantthresh;
  long   *quantmap;
  int     quantvals; 
  int     threshvals; 
} encode_aux_threshmatch;
typedef struct encode_aux_pigeonhole{
  float min;
  float del;
  int  mapentries;
  int  quantvals;
  long *pigeonmap;
  long fittotal;
  long *fitlist;
  long *fitmap;
  long *fitlength;
} encode_aux_pigeonhole;
typedef struct codebook{
  long dim;           
  long entries;       
  long used_entries;  
  const static_codebook *c;
  float        *valuelist;    
  ogg_uint32_t *codelist;   
  int          *dec_index;  
  char         *dec_codelengths;
  ogg_uint32_t *dec_firsttable;
  int           dec_firsttablen;
  int           dec_maxlength;
} codebook;
;
;
#define BLOCKTYPE_IMPULSE    0
#define BLOCKTYPE_PADDING    1
#define BLOCKTYPE_TRANSITION 0 
#define BLOCKTYPE_LONG       1
#define PACKETBLOBS 15
typedef struct vorbis_block_internal{
  float  **pcmdelay;   
  float  ampmax;
  int    blocktype;
  ogg_uint32_t   packetblob_markers[PACKETBLOBS];
} vorbis_block_internal;
typedef void vorbis_look_floor;
typedef void vorbis_look_residue;
typedef void vorbis_look_transform;
typedef struct {
  int blockflag;
  int windowtype;
  int transformtype;
  int mapping;
} vorbis_info_mode;
typedef void vorbis_info_floor;
typedef void vorbis_info_residue;
typedef void vorbis_info_mapping;
#define _V_PSY_H_
#define _V_SMFT_H_
typedef struct {
  int n;
  float *trigcache;
  int *splitcache;
} drft_lookup;
#define _vorbis_backend_h_
typedef struct{
  void                   (*pack)  (vorbis_info_floor *,oggpack_buffer *);
  vorbis_info_floor     *(*unpack)(vorbis_info *,oggpack_buffer *);
  vorbis_look_floor     *(*look)  (vorbis_dsp_state *,vorbis_info_floor *);
  void (*free_info) (vorbis_info_floor *);
  void (*free_look) (vorbis_look_floor *);
  void *(*inverse1)  (struct vorbis_block *,vorbis_look_floor *);
  int   (*inverse2)  (struct vorbis_block *,vorbis_look_floor *,
		     void *buffer,float *);
} vorbis_func_floor;
typedef struct{
  int   order;
  long  rate;
  long  barkmap;
  int   ampbits;
  int   ampdB;
  int   numbooks; 
  int   books[16];
  float lessthan;     
  float greaterthan;  
} vorbis_info_floor0;
#define VIF_POSIT 63
#define VIF_CLASS 16
#define VIF_PARTS 31
typedef struct{
  int   partitions;                
  int   partitionclass[VIF_PARTS]; 
  int   class_dim[VIF_CLASS];        
  int   class_subs[VIF_CLASS];       
  int   class_book[VIF_CLASS];       
  int   class_subbook[VIF_CLASS][8]; 
  int   mult;                       
  int   postlist[VIF_POSIT+2];     
  float maxover;     
  float maxunder;  
  float maxerr;    
  float twofitweight;  
  float twofitatten;
  int   n;
} vorbis_info_floor1;
typedef struct{
  void                 (*pack)  (vorbis_info_residue *,oggpack_buffer *);
  vorbis_info_residue *(*unpack)(vorbis_info *,oggpack_buffer *);
  vorbis_look_residue *(*look)  (vorbis_dsp_state *,
				 vorbis_info_residue *);
  void (*free_info)    (vorbis_info_residue *);
  void (*free_look)    (vorbis_look_residue *);
  long **(*class)      (struct vorbis_block *,vorbis_look_residue *,
			float **,int *,int);
  int  (*forward)      (struct vorbis_block *,vorbis_look_residue *,
			float **,float **,int *,int,long **);
  int  (*inverse)      (struct vorbis_block *,vorbis_look_residue *,
			float **,int *,int);
} vorbis_func_residue;
typedef struct vorbis_info_residue0{
  long  begin;
  long  end;
  int    grouping;         
  int    partitions;       
  int    groupbook;        
  int    secondstages[64]; 
  int    booklist[256];    
  float  classmetric1[64];  
  float  classmetric2[64];  
} vorbis_info_residue0;
typedef struct{
  void                 (*pack)  (vorbis_info *,vorbis_info_mapping *,
				 oggpack_buffer *);
  vorbis_info_mapping *(*unpack)(vorbis_info *,oggpack_buffer *);
  void (*free_info)    (vorbis_info_mapping *);
  int  (*forward)      (struct vorbis_block *vb);
  int  (*inverse)      (struct vorbis_block *vb,vorbis_info_mapping *);
} vorbis_func_mapping;
typedef struct vorbis_info_mapping0{
  int   submaps;  
  int   chmuxlist[256];   
  int   floorsubmap[16];   
  int   residuesubmap[16]; 
  int   coupling_steps;
  int   coupling_mag[256];
  int   coupling_ang[256];
} vorbis_info_mapping0;
#define P_BANDS 17      
#define P_LEVELS 8      
#define P_LEVEL_0 30.    
#define P_NOISECURVES 3
#define NOISE_COMPAND_LEVELS 40
typedef struct vorbis_info_psy{
  int   blockflag;
  float ath_adjatt;
  float ath_maxatt;
  float tone_masteratt[P_NOISECURVES];
  float tone_centerboost;
  float tone_decay;
  float tone_abs_limit;
  float toneatt[P_BANDS];
  int noisemaskp;
  float noisemaxsupp;
  float noisewindowlo;
  float noisewindowhi;
  int   noisewindowlomin;
  int   noisewindowhimin;
  int   noisewindowfixed;
  float noiseoff[P_NOISECURVES][P_BANDS];
  float noisecompand[NOISE_COMPAND_LEVELS];
  float max_curve_dB;
  int normal_channel_p;
  int normal_point_p;
  int normal_start;
  int normal_partition;
  double normal_thresh;
} vorbis_info_psy;
typedef struct{
  int   eighth_octave_lines;
  float preecho_thresh[VE_BANDS];
  float postecho_thresh[VE_BANDS];
  float stretch_penalty;
  float preecho_minenergy;
  float ampmax_att_per_sec;
  int   coupling_pkHz[PACKETBLOBS];  
  int   coupling_pointlimit[2][PACKETBLOBS];  
  int   coupling_prepointamp[PACKETBLOBS];  
  int   coupling_postpointamp[PACKETBLOBS];  
  int   sliding_lowpass[2][PACKETBLOBS];  
} vorbis_info_psy_global;
typedef struct {
  float ampmax;
  int   channels;
  vorbis_info_psy_global *gi;
  int   coupling_pointlimit[2][P_NOISECURVES];  
} vorbis_look_psy_global;
typedef struct {
  int n;
  struct vorbis_info_psy *vi;
  float ***tonecurves;
  float **noiseoffset;
  float *ath;
  long  *octave;             
  long  *bark;
  long  firstoc;
  long  shiftoc;
  int   eighth_octave_lines; 
  int   total_octave_lines;  
  long  rate; 
} vorbis_look_psy;
#define _V_BITRATE_H_
#define _OS_H
#define _V_RANDOM_H_
#  define _V_IFDEFJAIL_H_
#    define STIN static __inline__
#  define rint(x)   (floor((x)+0.5f))
#  define M_PI (3.1415926536f)
typedef int vorbis_fpu_control;
#  define vorbis_fpu_setround(vorbis_fpu_control) {}
#  define vorbis_fpu_restore(vorbis_fpu_control) {}
typedef struct bitrate_manager_state {
  ogg_uint32_t  *queue_binned;
  ogg_uint32_t  *queue_actual;
  int            queue_size;
  int            queue_head;
  int            queue_bins;
  long          *avg_binacc;
  int            avg_center;
  int            avg_tail;
  ogg_uint32_t   avg_centeracc;
  ogg_uint32_t   avg_sampleacc;
  ogg_uint32_t   avg_sampledesired;
  ogg_uint32_t   avg_centerdesired;
  long          *minmax_binstack;
  long          *minmax_posstack;
  long          *minmax_limitstack;
  long           minmax_stackptr;
  long           minmax_acctotal;
  int            minmax_tail;
  ogg_uint32_t   minmax_sampleacc;
  ogg_uint32_t   minmax_sampledesired;
  int            next_to_flush;
  int            last_to_flush;
  double         avgfloat;
  oggpack_buffer *packetbuffers;
  ogg_packet     *packets;
} bitrate_manager_state;
typedef struct bitrate_manager_info{
  double queue_avg_time;
  double queue_avg_center;
  double queue_minmax_time;
  double queue_hardmin;
  double queue_hardmax;
  double queue_avgmin;
  double queue_avgmax;
  double avgfloat_downslew_max;
  double avgfloat_upslew_max;
} bitrate_manager_info;
typedef struct private_state {
  envelope_lookup        *ve;     
  int                     window[2];
  vorbis_look_transform **transform[2];    
  drft_lookup             fft_look[2];
  int                     modebits;
  vorbis_look_floor     **flr;
  vorbis_look_residue   **residue;
  vorbis_look_psy        *psy;
  vorbis_look_psy_global *psy_g_look;
  unsigned char *header;
  unsigned char *header1;
  unsigned char *header2;
  bitrate_manager_state bms;
  ogg_int64_t sample_count;
} private_state;
typedef struct highlevel_byblocktype {
  double tone_mask_setting;
  double tone_peaklimit_setting;
  double noise_bias_setting;
  double noise_compand_setting;
} highlevel_byblocktype;
typedef struct highlevel_encode_setup {
  void *setup;
  int   set_in_stone;
  double base_setting;
  double long_setting;
  double short_setting;
  double impulse_noisetune;
  int    managed;
  long   bitrate_min;
  long   bitrate_av_lo;
  long   bitrate_av_hi;
  long   bitrate_max;
  double bitrate_limit_window;
  double bitrate_av_window;
  double bitrate_av_window_center;
  int impulse_block_p;
  int noise_normalize_p;
  double stereo_point_setting;
  double lowpass_kHz;
  double ath_floating_dB;
  double ath_absolute_dB;
  double amplitude_track_dBpersec;
  double trigger_setting;
  highlevel_byblocktype block[4]; 
} highlevel_encode_setup;
typedef struct codec_setup_info {
  long blocksizes[2];
  int        modes;
  int        maps;
  int        floors;
  int        residues;
  int        books;
  int        psys;     
  vorbis_info_mode       *mode_param[64];
  int                     map_type[64];
  vorbis_info_mapping    *map_param[64];
  int                     floor_type[64];
  vorbis_info_floor      *floor_param[64];
  int                     residue_type[64];
  vorbis_info_residue    *residue_param[64];
  static_codebook        *book_param[256];
  codebook               *fullbooks;
  vorbis_info_psy        *psy_param[4]; 
  vorbis_info_psy_global psy_g_param;
  bitrate_manager_info   bi;
  highlevel_encode_setup hi; 
  int         halfrate_flag;   
} codec_setup_info;
typedef struct {
  static_codebook *books[12][3];
} static_bookblock;
typedef struct {
  int res_type;
  int limit_type; 
  vorbis_info_residue0 *res;
  static_codebook  *book_aux;
  static_codebook  *book_aux_managed;
  static_bookblock *books_base;
  static_bookblock *books_base_managed;
} vorbis_residue_template;
typedef struct {
  vorbis_info_mapping0    *map;
  vorbis_residue_template *res;
} vorbis_mapping_template;
typedef struct vp_adjblock{
  int block[P_BANDS];
} vp_adjblock;
typedef struct {
  int data[NOISE_COMPAND_LEVELS];
} compandblock;
typedef struct {
  int att[P_NOISECURVES];
  float boost;
  float decay;
} att3;
typedef struct { int data[P_NOISECURVES]; } adj3; 
typedef struct {
  int   pre[PACKETBLOBS];
  int   post[PACKETBLOBS];
  float kHz[PACKETBLOBS];
  float lowpasskHz[PACKETBLOBS];
} adj_stereo;
typedef struct {
  int lo;
  int hi;
  int fixed;
} noiseguard;
typedef struct {
  int data[P_NOISECURVES][17];
} noise3;
typedef struct {
  int      mappings;
  double  *rate_mapping;
  double  *quality_mapping;
  int      coupling_restriction;
  long     samplerate_min_restriction;
  long     samplerate_max_restriction;
  int     *blocksize_short;
  int     *blocksize_long;
  att3    *psy_tone_masteratt;
  int     *psy_tone_0dB;
  int     *psy_tone_dBsuppress;
  vp_adjblock *psy_tone_adj_impulse;
  vp_adjblock *psy_tone_adj_long;
  vp_adjblock *psy_tone_adj_other;
  noiseguard  *psy_noiseguards;
  noise3      *psy_noise_bias_impulse;
  noise3      *psy_noise_bias_padding;
  noise3      *psy_noise_bias_trans;
  noise3      *psy_noise_bias_long;
  int         *psy_noise_dBsuppress;
  compandblock  *psy_noise_compand;
  double        *psy_noise_compand_short_mapping;
  double        *psy_noise_compand_long_mapping;
  int      *psy_noise_normal_start[2];
  int      *psy_noise_normal_partition[2];
  double   *psy_noise_normal_thresh;
  int      *psy_ath_float;
  int      *psy_ath_abs;
  double   *psy_lowpass;
  vorbis_info_psy_global *global_params;
  double     *global_mapping;
  adj_stereo *stereo_modes;
  static_codebook ***floor_books;
  vorbis_info_floor1 *floor_params;
  int *floor_short_mapping;
  int *floor_long_mapping;
  vorbis_mapping_template *maps;
} ve_setup_data_template;
#define _OV_FILE_H_
typedef struct {
  size_t (*read_func)  (void *ptr, size_t size, size_t nmemb, void *datasource);
  int    (*seek_func)  (void *datasource, ogg_int64_t offset, int whence);
  int    (*close_func) (void *datasource);
  long   (*tell_func)  (void *datasource);
} ov_callbacks;
#define  NOTOPEN   0
#define  PARTOPEN  1
#define  OPENED    2
#define  STREAMSET 3
#define  INITSET   4
typedef struct OggVorbis_File {
  void            *datasource; 
  int              seekable;
  ogg_int64_t      offset;
  ogg_int64_t      end;
  ogg_sync_state   oy; 
  int              links;
  ogg_int64_t     *offsets;
  ogg_int64_t     *dataoffsets;
  long            *serialnos;
  ogg_int64_t     *pcmlengths; 
  vorbis_info     *vi;
  vorbis_comment  *vc;
  ogg_int64_t      pcm_offset;
  int              ready_state;
  long             current_serialno;
  int              current_link;
  double           bittrack;
  double           samptrack;
  ogg_stream_state os; 
  vorbis_dsp_state vd; 
  vorbis_block     vb; 
  ov_callbacks callbacks;
} OggVorbis_File;
#define CHUNKSIZE 8500 
#define _V_REG_H_
#define VI_TRANSFORMB 1
#define VI_WINDOWB 1
#define VI_TIMEB 1
#define VI_FLOORB 2
#define VI_RESB 3
#define VI_MAPB 1
#define _V_WINDOW_
#define _V_LPC_H_
#define WORD_ALIGN 8
#define _V_SCALES_H_
#define VORBIS_IEEE_FLOAT32 1
#define FABS(x) fabs(*(x))
#define todB(x)   (*(x)==0?-400.f:log(*(x)**(x))*4.34294480f)
#define todB_nn(x)   (*(x)==0.f?-400.f:log(*(x))*8.6858896f)
#define fromdB(x) (exp((x)*.11512925f))  
#define toBARK(n)   (13.1f*atan(.00074f*(n))+2.24f*atan((n)*(n)*1.85e-8f)+1e-4f*(n))
#define fromBARK(z) (102.f*(z)-2.f*pow(z,2.f)+.4f*pow(z,3.f)+pow(1.46f,z)-1.f)
#define toMEL(n)    (log(1.f+(n)*.001f)*1442.695f)
#define fromMEL(m)  (1000.f*exp((m)/1442.695f)-1000.f)
#define toOC(n)     (log(n)*1.442695f-5.965784f)
#define fromOC(o)   (exp(((o)+5.965784f)*.693147f))
#define LIMITBYTES(pos,bin) (bm->minmax_binstack[(pos)*bins*2+((bin)+bins)])
#define VQ_FEXP 10
#define VQ_FMAN 21
#define VQ_FEXP_BIAS 768 
STIN long decode_packed_entry_number(codebook *book, oggpack_buffer *b);
STIN void mdct_butterfly_8(DATA_TYPE *x);
STIN void mdct_butterfly_16(DATA_TYPE *x);
STIN void mdct_butterfly_32(DATA_TYPE *x);
STIN void mdct_butterfly_first(DATA_TYPE *T,
					DATA_TYPE *x,
					int points);
STIN void mdct_butterfly_generic(DATA_TYPE *T,
					  DATA_TYPE *x,
					  int points,
					  int trigint);
STIN void mdct_butterflies(mdct_lookup *init,
			     DATA_TYPE *x,
			     int points);
STIN void mdct_bitreverse(mdct_lookup *init, 
			    DATA_TYPE *x);
#define _V_MASKING_H_
#define MAX_ATH 88
#define EHMER_OFFSET 16
#define EHMER_MAX 56
#define NEGINF -9999.f
#if 0
static int seq=0;
static ogg_int64_t totalshift=-1024;
#endif
#define _V_LSP_H_
typedef struct {
  int ln;
  int  m;
  int **linearmap;
  int  n[2];
  vorbis_info_floor0 *vi;
  long bits;
  long frames;
} vorbis_look_floor0;
#define   FLOAT_LOOKUP
#undef    INT_LOOKUP
#define COS_LOOKUP_SZ 128
#define INVSQ_LOOKUP_SZ 32
#define INVSQ2EXP_LOOKUP_MIN (-32)
#define INVSQ2EXP_LOOKUP_MAX 32
#define FROMdB_LOOKUP_SZ 35
#define FROMdB2_LOOKUP_SZ 32
#define FROMdB_SHIFT 5
#define FROMdB2_SHIFT 3
#define FROMdB2_MASK 31
#define EPSILON 10e-7
#define floor1_rangedB 140 
typedef struct {
  int sorted_index[VIF_POSIT+2];
  int forward_index[VIF_POSIT+2];
  int reverse_index[VIF_POSIT+2];
  int hineighbor[VIF_POSIT];
  int loneighbor[VIF_POSIT];
  int posts;
  int n;
  int quant_q;
  vorbis_info_floor1 *vi;
  long phrasebits;
  long postbits;
  long frames;
} vorbis_look_floor1;
typedef struct lsfit_acc{
  long x0;
  long x1;
  long xa;
  long ya;
  long x2a;
  long y2a;
  long xya; 
  long an;
} lsfit_acc;
typedef struct {
  vorbis_info_residue0 *info;
  int         parts;
  int         stages;
  codebook   *fullbooks;
  codebook   *phrasebook;
  codebook ***partbooks;
  int         partvals;
  int       **decodemap;
  long      postbits;
  long      phrasebits;
  long      frames;
} vorbis_look_residue0;
#if 0
long **res0_class(vorbis_block *vb,vorbis_look_residue *vl,
		  float **in,int *nonzero,int ch){
  int i,used=0;
  for(i=0;i<ch;i++)
    if(nonzero[i])
      in[used++]=in[i];
  if(used)
    return(_01class(vb,vl,in,used));
  else
    return(0);
}
int res0_forward(vorbis_block *vb,vorbis_look_residue *vl,
		 float **in,float **out,int *nonzero,int ch,
		 long **partword){
  int i,j,used=0,n=vb->pcmend/2;
  for(i=0;i<ch;i++)
    if(nonzero[i]){
      if(out)
	for(j=0;j<n;j++)
	  out[i][j]+=in[i][j];
      in[used++]=in[i];
    }
  if(used){
    int ret=_01forward(vb,vl,in,used,partword,
		      _interleaved_encodepart);
    if(out){
      used=0;
      for(i=0;i<ch;i++)
	if(nonzero[i]){
	  for(j=0;j<n;j++)
	    out[i][j]-=in[used][j];
	  used++;
	}
    }
    return(ret);
  }else{
    return(0);
  }
}
#endif
#if 0
static long seq=0;
static ogg_int64_t total=0;
static float FLOOR1_fromdB_LOOKUP[256]={
  1.0649863e-07F, 1.1341951e-07F, 1.2079015e-07F, 1.2863978e-07F, 
  1.3699951e-07F, 1.4590251e-07F, 1.5538408e-07F, 1.6548181e-07F, 
  1.7623575e-07F, 1.8768855e-07F, 1.9988561e-07F, 2.128753e-07F, 
  2.2670913e-07F, 2.4144197e-07F, 2.5713223e-07F, 2.7384213e-07F, 
  2.9163793e-07F, 3.1059021e-07F, 3.3077411e-07F, 3.5226968e-07F, 
  3.7516214e-07F, 3.9954229e-07F, 4.2550680e-07F, 4.5315863e-07F, 
  4.8260743e-07F, 5.1396998e-07F, 5.4737065e-07F, 5.8294187e-07F, 
  6.2082472e-07F, 6.6116941e-07F, 7.0413592e-07F, 7.4989464e-07F, 
  7.9862701e-07F, 8.5052630e-07F, 9.0579828e-07F, 9.6466216e-07F, 
  1.0273513e-06F, 1.0941144e-06F, 1.1652161e-06F, 1.2409384e-06F, 
  1.3215816e-06F, 1.4074654e-06F, 1.4989305e-06F, 1.5963394e-06F, 
  1.7000785e-06F, 1.8105592e-06F, 1.9282195e-06F, 2.0535261e-06F, 
  2.1869758e-06F, 2.3290978e-06F, 2.4804557e-06F, 2.6416497e-06F, 
  2.8133190e-06F, 2.9961443e-06F, 3.1908506e-06F, 3.3982101e-06F, 
  3.6190449e-06F, 3.8542308e-06F, 4.1047004e-06F, 4.3714470e-06F, 
  4.6555282e-06F, 4.9580707e-06F, 5.2802740e-06F, 5.6234160e-06F, 
  5.9888572e-06F, 6.3780469e-06F, 6.7925283e-06F, 7.2339451e-06F, 
  7.7040476e-06F, 8.2047000e-06F, 8.7378876e-06F, 9.3057248e-06F, 
  9.9104632e-06F, 1.0554501e-05F, 1.1240392e-05F, 1.1970856e-05F, 
  1.2748789e-05F, 1.3577278e-05F, 1.4459606e-05F, 1.5399272e-05F, 
  1.6400004e-05F, 1.7465768e-05F, 1.8600792e-05F, 1.9809576e-05F, 
  2.1096914e-05F, 2.2467911e-05F, 2.3928002e-05F, 2.5482978e-05F, 
  2.7139006e-05F, 2.8902651e-05F, 3.0780908e-05F, 3.2781225e-05F, 
  3.4911534e-05F, 3.7180282e-05F, 3.9596466e-05F, 4.2169667e-05F, 
  4.4910090e-05F, 4.7828601e-05F, 5.0936773e-05F, 5.4246931e-05F, 
  5.7772202e-05F, 6.1526565e-05F, 6.5524908e-05F, 6.9783085e-05F, 
  7.4317983e-05F, 7.9147585e-05F, 8.4291040e-05F, 8.9768747e-05F, 
  9.5602426e-05F, 0.00010181521F, 0.00010843174F, 0.00011547824F, 
  0.00012298267F, 0.00013097477F, 0.00013948625F, 0.00014855085F, 
  0.00015820453F, 0.00016848555F, 0.00017943469F, 0.00019109536F, 
  0.00020351382F, 0.00021673929F, 0.00023082423F, 0.00024582449F, 
  0.00026179955F, 0.00027881276F, 0.00029693158F, 0.00031622787F, 
  0.00033677814F, 0.00035866388F, 0.00038197188F, 0.00040679456F, 
  0.00043323036F, 0.00046138411F, 0.00049136745F, 0.00052329927F, 
  0.00055730621F, 0.00059352311F, 0.00063209358F, 0.00067317058F, 
  0.00071691700F, 0.00076350630F, 0.00081312324F, 0.00086596457F, 
  0.00092223983F, 0.00098217216F, 0.0010459992F, 0.0011139742F, 
  0.0011863665F, 0.0012634633F, 0.0013455702F, 0.0014330129F, 
  0.0015261382F, 0.0016253153F, 0.0017309374F, 0.0018434235F, 
  0.0019632195F, 0.0020908006F, 0.0022266726F, 0.0023713743F, 
  0.0025254795F, 0.0026895994F, 0.0028643847F, 0.0030505286F, 
  0.0032487691F, 0.0034598925F, 0.0036847358F, 0.0039241906F, 
  0.0041792066F, 0.0044507950F, 0.0047400328F, 0.0050480668F, 
  0.0053761186F, 0.0057254891F, 0.0060975636F, 0.0064938176F, 
  0.0069158225F, 0.0073652516F, 0.0078438871F, 0.0083536271F, 
  0.0088964928F, 0.009474637F, 0.010090352F, 0.010746080F, 
  0.011444421F, 0.012188144F, 0.012980198F, 0.013823725F, 
  0.014722068F, 0.015678791F, 0.016697687F, 0.017782797F, 
  0.018938423F, 0.020169149F, 0.021479854F, 0.022875735F, 
  0.024362330F, 0.025945531F, 0.027631618F, 0.029427276F, 
  0.031339626F, 0.033376252F, 0.035545228F, 0.037855157F, 
  0.040315199F, 0.042935108F, 0.045725273F, 0.048696758F, 
  0.051861348F, 0.055231591F, 0.058820850F, 0.062643361F, 
  0.066714279F, 0.071049749F, 0.075666962F, 0.080584227F, 
  0.085821044F, 0.091398179F, 0.097337747F, 0.10366330F, 
  0.11039993F, 0.11757434F, 0.12521498F, 0.13335215F, 
  0.14201813F, 0.15124727F, 0.16107617F, 0.17154380F, 
  0.18269168F, 0.19456402F, 0.20720788F, 0.22067342F, 
  0.23501402F, 0.25028656F, 0.26655159F, 0.28387361F, 
  0.30232132F, 0.32196786F, 0.34289114F, 0.36517414F, 
  0.38890521F, 0.41417847F, 0.44109412F, 0.46975890F, 
  0.50028648F, 0.53279791F, 0.56742212F, 0.60429640F, 
  0.64356699F, 0.68538959F, 0.72993007F, 0.77736504F, 
  0.82788260F, 0.88168307F, 0.9389798F, 1.F, 
};
#endif 
#define BUFFER_INCREMENT 256
#undef BUFFER_INCREMENT
#if 0
static ogg_uint32_t _ogg_crc_entry(unsigned long index){
  int           i;
  unsigned long r;
  r = index << 24;
  for (i=0; i<8; i++)
    if (r & 0x80000000UL)
      r = (r << 1) ^ 0x04c11db7; 
    else
       r<<=1;
 return (r & 0xffffffffUL);
}
#endif
