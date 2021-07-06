#ifndef _CD_CGM_
#define _CD_CGM_

#ifdef __cplusplus
extern "C" {
#endif

cdContext* cdContextCGM(void);
#define CD_CGM cdContextCGM()

#define CD_CGMCOUNTERCB 1
#define CD_CGMSCLMDECB 2
#define CD_CGMVDCEXTCB 3
#define CD_CGMBEGPICTCB 4
#define CD_CGMBEGPICTBCB 5
#define CD_CGMBEGMTFCB 6

/* OLD definitions, defined for backward compatibility */
#define CDPLAY_ABORT CD_ABORT
#define CDPLAY_GO CD_CONTINUE

#ifdef __cplusplus
}
#endif

#endif /* ifndef _CD_CGM_ */


