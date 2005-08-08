/*
 * The contents of this file are subject to the AOLserver Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://aolserver.com/.
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Original Code is AOLserver Code and related documentation
 * distributed by AOL.
 * 
 * The Initial Developer of the Original Code is America Online,
 * Inc. Portions created by AOL are Copyright (C) 1999 America Online,
 * Inc. All Rights Reserved.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU General Public License (the "GPL"), in which case the
 * provisions of GPL are applicable instead of those above.  If you wish
 * to allow use of your version of this file only under the terms of the
 * GPL and not to allow others to use your version of this file under the
 * License, indicate your decision by deleting the provisions above and
 * replace them with the notice and other provisions required by the GPL.
 * If you do not delete the provisions above, a recipient may use your
 * version of this file under either the License or the GPL.
 */

/* 
 * nsdb.c --
 *
 *	Database module entry point.
 */

static const char *RCSID = "@(#) $Header: /Users/dossy/Desktop/cvs/aolserver/nsdb/nsdb.c,v 1.3 2005/08/08 11:32:17 jgdavidson Exp $, compiled: " __DATE__ " " __TIME__;

#include "db.h"


/*
 *----------------------------------------------------------------------
 *
 * NsDb_ModInit --
 *
 *	Module initialization point.
 *
 * Results:
 *	NS_OK.
 *
 * Side effects:
 *	May load database drivers and configure pools.
 *
 *----------------------------------------------------------------------
 */

int
NsDb_ModInit(char *server, char *module)
{
    static int once;

    if (server == NULL) {
	Ns_Log(Error, "%s: attempt to load outside a virual server", module);
	return NS_ERROR;
    }
    if (!once) {
	NsDbInitPools();
	once = 1;
    }
    NsDbInitServer(server);
    return Ns_TclInitInterps(server, NsDbAddCmds, server);
}
