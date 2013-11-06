
// ******************************************************************
// Copyright (c) 2002- Satoshi, All Rights Reserved.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//
// Author : Satoshi ( af230533@im07.alpha-net.ne.jp )
// ******************************************************************

// **********************************************************************
// ZBench À°¿ôÃÍ¤Î·×»»
// Copyright (C) Satoshi 1994-2003 All rights reserved.
// ***********************************************************************

#include <time.h>

#define       INT_TEST_COUNT      170                 // Bench Integer 150-->170

extern        double        TestData[];

// ********************************************************************
// BenchInteger   for Windows
// ********************************************************************
// 2003.06.06 update rand()
// **********************************************************************
void   BenchInteger( void )
{
  int         i;
  int         j;
  int         k;
  long        dummy;
/*-------------------------------- 2003.06.06 delete !
  long        xx[INT_TEST_COUNT];
  long        yy[INT_TEST_COUNT];
  long        zz[INT_TEST_COUNT];
---------------------------------------------------*/
  long        xx;
  long        yy;
  long        zz;

/*-------------------------------- 2003.06.06 delete !
  for ( i= 0 ; i < INT_TEST_COUNT ; i++ )
  {
      xx[i] = (long)( TestData[i] * 10000 );
      yy[i] = (long)( TestData[i] * 1000 );
      zz[i] = xx[i] - yy[i];
  }
---------------------------------------------------*/
  srand( time( NULL ) );

  for ( i= 0 ; i < INT_TEST_COUNT ; i++ )
  {
      for ( j= 0 ; j < INT_TEST_COUNT ; j++ )
      {
          for( k= 0 ; k < INT_TEST_COUNT ; k++ )
          {
              xx = ( rand() % 1000 + 111 ) * 7 / 3 + 31;
              yy = ( rand() % 100 + 23 ) * 11 / 7 + 17;
              zz = ( rand() % 100 + 47 ) * 13 / 11 - 211;
              dummy = xx * yy / zz;
              dummy *= 23;
              dummy += ( xx - yy + zz );
              dummy -= ( xx + yy - zz );
              dummy *= ( xx % zz / yy );
              dummy /= ( xx % yy * zz );
          }
      }
  }
  return;
}
