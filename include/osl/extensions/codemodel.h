
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/codemodel.h                      **
     **-----------------------------------------------------------------**
     **                   First version: 11/02/2016                     **
     **-----------------------------------------------------------------**


 *****************************************************************************
 * OpenScop: Structures and formats for polyhedral tools to talk together    *
 *****************************************************************************
 *    ,___,,_,__,,__,,__,,__,,_,__,,_,__,,__,,___,_,__,,_,__,                *
 *    /   / /  //  //  //  // /   / /  //  //   / /  // /  /|,_,             *
 *   /   / /  //  //  //  // /   / /  //  //   / /  // /  / / /\             *
 *  |~~~|~|~~~|~~~|~~~|~~~|~|~~~|~|~~~|~~~|~~~|~|~~~|~|~~~|/_/  \            *
 *  | G |C| P | = | L | P |=| = |C| = | = | = |=| = |=| C |\  \ /\           *
 *  | R |l| o | = | e | l |=| = |a| = | = | = |=| = |=| L | \# \ /\          *
 *  | A |a| l | = | t | u |=| = |n| = | = | = |=| = |=| o | |\# \  \         *
 *  | P |n| l | = | s | t |=| = |d| = | = | = | |   |=| o | | \# \  \        *
 *  | H | | y |   | e | o | | = |l|   |   | = | |   | | G | |  \  \  \       *
 *  | I | |   |   | e |   | |   | |   |   |   | |   | |   | |   \  \  \      *
 *  | T | |   |   |   |   | |   | |   |   |   | |   | |   | |    \  \  \     *
 *  | E | |   |   |   |   | |   | |   |   |   | |   | |   | |     \  \  \    *
 *  | * |*| * | * | * | * |*| * |*| * | * | * |*| * |*| * | /      \* \  \   *
 *  | O |p| e | n | S | c |o| p |-| L | i | b |r| a |r| y |/        \  \ /   *
 *  '---'-'---'---'---'---'-'---'-'---'---'---'-'---'-'---'          '--'    *
 *                                                                           *
 * Copyright (C) 2008 University Paris-Sud 11 and INRIA                      *
 *                                                                           *
 * (3-clause BSD license)                                                    *
 * Redistribution and use in source  and binary forms, with or without       *
 * modification, are permitted provided that the following conditions        *
 * are met:                                                                  *
 *                                                                           *
 * 1. Redistributions of source code must retain the above copyright notice, *
 *    this list of conditions and the following disclaimer.                  *
 * 2. Redistributions in binary form must reproduce the above copyright      *
 *    notice, this list of conditions and the following disclaimer in the    *
 *    documentation and/or other materials provided with the distribution.   *
 * 3. The name of the author may not be used to endorse or promote products  *
 *    derived from this software without specific prior written permission.  *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR      *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.   *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,          *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT  *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY     *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT       *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF  *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.         *
 *                                                                           *
 * OpenScop Library, a library to manipulate OpenScop formats and data       *
 * structures. Written by:                                                   *
 * Cedric Bastoul     <Cedric.Bastoul@u-psud.fr>,                            *
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr> and                      *
 * Oleksandr Zinenko  <Oleksandr.Zinenko@inria.fr>                           *
 *                                                                           *
 *****************************************************************************/

#ifndef OSL_CODEMODEL_H
#define OSL_CODEMODEL_H

#include <stdio.h>
#include <osl/interface.h>
#include <osl/extensions/coordinates.h>

#if defined(__cplusplus)
extern "C"
  {
#endif

#define OSL_URI_CODEMODEL "codemodel"

/** Defines kinds of the code model nodes, see \ref osl_codemodel::kind. */
enum {
  OSL_CODEMODEL_LOOP,     /**< This node wraps an \ref osl_codemodel_loop. */
  OSL_CODEMODEL_STMT,     /**< This node wraps an \ref osl_codemodel_stmt. */
  OSL_CODEMODEL_UNDEFINED /**< This node does not wrap anything. */
};

/**
 * Stores coordinates and identifier for the loop in the code representation
 * of the SCoP.
 */
struct osl_codemodel_loop {
  /** Loop sequential identifier. */
  int id;
  /** Coordinates of the entire loop nest. */
  osl_coordinates_p coordinates;
  /** Coordinates of the loop initialization expression (<code>i = 1;</code>)*/
  osl_coordinates_p initializer_coordinates;
  /** Coordinates ot the loop condition expression (<code>i <= 42;</code>)*/
  osl_coordinates_p condition_coordinates;
  /** Coordinates of the loop increment expression (<code>i++</code>)*/
  osl_coordinates_p increment_coordinates;
};
typedef struct osl_codemodel_loop   osl_codemodel_loop_t;
typedef struct osl_codemodel_loop * osl_codemodel_loop_p;

/**
 * Stores coordinates and parent loop identifier for the statement in the code
 * representation of the SCoP.
 */
struct osl_codemodel_stmt {
  /** Sequential identifier of the innermost loop enclosing this statement, in
   *  the same code model. */
  int parent_id;
  /** Coordinates of the statement. */
  osl_coordinates_p coordinates;
};

typedef struct osl_codemodel_stmt   osl_codemodel_stmt_t;
typedef struct osl_codemodel_stmt * osl_codemodel_stmt_p;

/**
 * A tree-like code model node for the loops and statements representing this
 * SCoP in the code.  This node may wrap loops or statements.  The code model
 * is represented by a root node, that is always a loop with all the other
 * entities as its children.  This pseudo-loop has all coordinates \c NULL.  A
 * loop node may have an arbitrary number of child nodes.  A statement node is
 * not supposed to have any children.
 */
struct osl_codemodel {
  union {
    struct osl_codemodel_loop *loop;
    struct osl_codemodel_stmt *stmt;
  } u;                            /**< Wrapped code entity. */
  int kind;                       /**< Kind of entity wrapped in u.*/
  int nb_children;                /**< Number of child nodes.*/
  struct osl_codemodel **children;/**< Pointers to child nodes.*/
};

typedef struct osl_codemodel   osl_codemodel_t;
typedef struct osl_codemodel * osl_codemodel_p;

void            osl_codemodel_idump(FILE *, osl_codemodel_p, int);
void            osl_codemodel_dump(FILE *, osl_codemodel_p);
char *          osl_codemodel_sprint(osl_codemodel_p);

osl_codemodel_p osl_codemodel_sread(char **);

osl_codemodel_p osl_codemodel_malloc();
osl_codemodel_p osl_codemodel_create_loop();
osl_codemodel_p osl_codemodel_create_stmt();
void            osl_codemodel_free(osl_codemodel_p);

osl_codemodel_p osl_codemodel_clone(osl_codemodel_p);
int             osl_codemodel_equal(osl_codemodel_p, osl_codemodel_p);
osl_interface_p osl_codemodel_interface();
void            osl_codemodel_add_child(osl_codemodel_p, osl_codemodel_p);
void            osl_codemodel_remove_child(osl_codemodel_p, osl_codemodel_p);
void            osl_codemodel_update_identifiers(osl_codemodel_p);

#if defined(__cplusplus)
  }
#endif

#endif //OSL_CODEMODEL_H
