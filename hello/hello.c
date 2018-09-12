#ifdef CInfo
#define GatherCopyInfo 1
#endif

#ifdef FInfo
#define GatherFlopInfo 1
#endif

#define _INTRINSICS_ 1

#include "sisal.h"

extern int sisal_file_io;

int ProvideModuleDataBaseOnAllCompiles;

static void InitGlobalData();

#undef _MAIN
static void         _MAIN();	/* [Call=F,Rec=F,Par=F,Xmk=F,Mk=e] */
#undef IReadCharVector
static POINTER      IReadCharVector();
#undef IWriteCharVector
static void         IWriteCharVector();
#undef SFreeCharVector
static void         SFreeCharVector();
#undef PFreeCharVector
static void         PFreeCharVector();

struct Args12 {   
struct ActRec *FirstAR; int Count;   
POINTER Out1;   
  };

static void ArrCharCopy( dest, source, num )
POINTER  dest;
POINTER  source;
register int num;
{
  register int  i;
  register char  *src = (char*) source;
  register char  *dst = (char*) dest;
  MyBCopy( src, dst, num );
}

static shared char Storage1[17] = {
  'H',
  'e',
  'l',
  'l',
  'o',
  ' ',
  'm',
  'y',
  ' ',
  'w',
  'o',
  'r',
  'l',
  'd',
  '!',
  ' ',
  '2' 
  };

static shared PHYS Phys1 = APhysStruct(
  17, (POINTER)Storage1, 0, 1, 0, (POINTER)0, 1
  );

static shared ARRAY gbl1Data = AStruct(
  (POINTER) (Storage1 - (1)), 1, 17, &Phys1, 0, 0, 1000000002
  );

static shared POINTER gbl1 = (POINTER) &gbl1Data;

static void _MAIN( args )
FUNCTION args;
{

#undef  MY_LOCK
#undef  MY_UNLOCK
#define MY_LOCK(x)
#define MY_UNLOCK(x)

  IncRefCount( gbl1, ARRAY, 1 );
  ((struct Args12*)args)->Out1 = gbl1;

#undef  MY_LOCK
#undef  MY_UNLOCK
#define MY_LOCK(x)    MY_LOCK_BACKUP(x)
#define MY_UNLOCK(x)  MY_UNLOCK_BACKUP(x)
}

static int *GInit = NULL;

static void InitGlobalData()
{
  SLockParent;

  if ( GInit == NULL )
    GInit = (int *) Alloc( sizeof(int) );
  else if ( *GInit ) {
    SUnlockParent;
    return;
    }

  *GInit = TRUE;

  MY_INIT_LOCK( &(gbl1Data.Phys->Mutex) );
  MY_INIT_LOCK( &(gbl1Data.Mutex) );

  SUnlockParent;
}

void SisalMain( args )
POINTER args;
{
#ifdef CInfo
  SaveCopyInfo;
#endif
#ifdef FInfo
  SaveFlopInfo;
#endif
  InitGlobalData();
  /* Set file I/O flag for output... */
  sisal_file_io = 0;
  _MAIN( args );
}

#undef GatherCopyInfo

FUNCTION ReadFibreInputs()
{
  int previous_io_state = sisal_file_io;
  register struct Args12 *args = (struct Args12*) Alloc( sizeof( struct Args12 ) );
  /* Set file I/O flag for input... */
  sisal_file_io = 0;
  sisal_file_io = previous_io_state;
  return( (FUNCTION) args );
}

#ifdef CInfo
#define GatherCopyInfo 1
#endif

void WriteFibreOutputs( args )
FUNCTION args;
{
  int previous_io_state = sisal_file_io;
  register struct Args12 *p = (struct Args12*) args;
  /* Set file I/O flag for input... */
  sisal_file_io = 0;
  WriteCharVector( (p->Out1) );
  sisal_file_io = previous_io_state;
}
