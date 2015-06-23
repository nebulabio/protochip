// CheapStat sample sizes

#define kSize_MaxSamplesSWV   1000
#define kSize_MaxSamplesCV    1500
#define kSize_MaxSamplesLSV   1500
#define kSize_MaxSamplesCA    1500
#define kSize_MaxSamplesACV   50

// CheapStat command types //

// incomming commands
#define kRxCommand_SampleSWV         0
#define kRxCommand_SampleCV          1
#define kRxCommand_SampleACV         2
#define kRxCommand_SampleLSV         3
#define kRxCommand_SampleCONSTVOLT   4 // Unused?
#define kRxCommand_SampleCA          5
#define kRxCommand_ProfileList       'z'

// outgoing commands
#define kTxCommand_SendProfile       'u'
#define kTxCommand_GetProfileList    'd'

typedef struct SWV
{
  int16_t   freq;
  int16_t   start;
  int16_t   stop;
  int16_t   height;
  int16_t   increment;
  uint8_t   currRange;
  uint16_t  numSamples;
  int16_t   forwardCurrentSamples[kSize_MaxSamplesSWV/2];
  int16_t   reverseCurrentSamples[kSize_MaxSamplesSWV/2];
}SWV; // length = 13 // length = 31 + i * 4 bytes

//@@ Review types of variables below. Not all are unsigned.
typedef struct CV
{
  uint16_t slope;
  uint16_t start;
  uint16_t stop;
  uint16_t scans;
  uint16_t sample_rate;
  uint8_t  curr_range;
  uint16_t numSamples;
  uint16_t current[kSize_MaxSamplesCV];
}CV; //length = 27 + i * 2 bytes

typedef struct ACV
{
  uint16_t freq;
  uint16_t height;
  uint16_t cycles;
  uint16_t start;
  uint16_t stop;
  uint16_t increment;
  uint8_t  curr_range;
  uint16_t numSamples;
  uint16_t magnitude[kSize_MaxSamplesACV];
  uint16_t phase[kSize_MaxSamplesACV];
}ACV; // length = 33 + k * 4 bytes

typedef struct LSV
{
  uint16_t  settle;
  uint16_t  start;
  uint16_t  slope;
  uint16_t  sample_rate;
  uint8_t   curr_rage;
  uint16_t  numSamples;
  uint16_t  current[kSize_MaxSamplesLSV];
}LSV; // total length = 29 + i * 2 bytes

typedef struct CA
{
  uint16_t  wait_time;
  uint16_t  step_voltage;
  uint16_t  step_width; 
  uint16_t  quiet_time;
  uint16_t  sample_rate;
  uint8_t   steps;
  uint8_t   curr_range;
  uint16_t  length;
  uint16_t  samples[kSize_MaxSamplesCA];
}CA; // total length = 30 + i * 2 bytes
