
    /*+-----------------------------------------------------------------**
     **                       OpenScop Library                          **
     **-----------------------------------------------------------------**
     **                     extensions/codemodel.c                      **
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
 * Louis-Noel Pouchet <Louis-Noel.pouchet@inria.fr>                          *
 * Oleksandr Zinenko  <Oleksandr.Zinenko@inria.fr>                           *
 *                                                                           *
 *****************************************************************************/

#include <osl/extensions/codemodel.h>
#include <osl/extensions/coordinates.h>
#include <osl/macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*+***************************************************************************
 *                          Structure display function                       *
 *****************************************************************************/


/**
 * Prints an osl_codemodel structure (#codemodel) into a
 * file (\c FILE*, possibly \c stdout) in a way that tends to be
 * understandable. It includes an indentation level (#level) in order to work
 * with others idump functions.
 * \param file        The file where the information has to be printed.
 * \param codemodel   The codemodel structure to print.
 * \param level       Number of spaces before printing, for each line.
 */
void osl_codemodel_idump(FILE *file, osl_codemodel_p codemodel, int level) {
  int i, j;

  for (i = 0; i < level; ++i)
    fprintf(file, "|\t");

  if (codemodel != NULL)
    fprintf(file, "+-- osl_codemodel_t\n");
  else
    fprintf(file, "+-- NULL codemodel\n");

  if (codemodel != NULL) {
    if (codemodel->kind == OSL_CODEMODEL_LOOP) {
      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      fprintf(file, "Loop %d\n", codemodel->u.loop->id);

      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      if (codemodel->u.loop->coordinates != NULL) {
        fprintf(file, "Coordinates\n");
        osl_coordinates_idump(file, codemodel->u.loop->coordinates,
                              level + 1);
      } else {
        fprintf(file, "NULL prefix coordinates\n");
      }

      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      if (codemodel->u.loop->initializer_coordinates != NULL) {
        fprintf(file, "Initializer coordinates\n");
        osl_coordinates_idump(file, codemodel->u.loop->initializer_coordinates,
                              level + 1);
      } else {
        fprintf(file, "NULL initializer coordinates\n");
      }

      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      if (codemodel->u.loop->condition_coordinates != NULL) {
        fprintf(file, "Condition coordinates\n");
        osl_coordinates_idump(file, codemodel->u.loop->condition_coordinates,
                              level + 1);
      } else {
        fprintf(file, "NULL condition coordinates\n");
      }

      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      if (codemodel->u.loop->increment_coordinates != NULL) {
        fprintf(file, "Increment coordinates\n");
        osl_coordinates_idump(file, codemodel->u.loop->increment_coordinates,
                              level + 1);
      } else {
        fprintf(file, "NULL increment coordinates\n");
      }
    } else if (codemodel->kind == OSL_CODEMODEL_STMT) {
      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      fprintf(file, "Statement (parent loop ID %d)\n", codemodel->u.stmt->parent_id);

      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      if (codemodel->u.stmt->coordinates != NULL) {
        fprintf(file, "Coordinates\n");
        osl_coordinates_idump(file, codemodel->u.stmt->coordinates,
                              level + 1);
      } else {
        fprintf(file, "NULL coordinates\n");
      }
    } else {
      for (i = 0; i <= level; ++i)
        fprintf(file, "|\t");
      fprintf(file, "Undefined codemodel subtype\n");
    }

    for (j = 0; j < codemodel->nb_children; ++j) {
      osl_codemodel_idump(file, codemodel->children[j], level + 1);
    }
  }
}

/**
 * Prints the content of an osl_codemodel_t structure (#codemodel) into a file
 * (\c FILE*, possibly \c stdout).
 * \param file        The file where the information has to be printed.
 * \param codemodel   The codemodel structure to print.
 */
void osl_codemodel_dump(FILE *file, osl_codemodel_p codemodel) {
  osl_codemodel_idump(file, codemodel, 0);
}

/**
 * Prints the content of an \ref osl_codemodel_t structure
 * (#codemodel) into a string (returned) in the OpenScop textual format.
 * \param  codemodel The codemodel structure to be print.
 * \return           A string containing the OpenScop dump of the codemodel
 *                   structure.
 */
char *osl_codemodel_sprint(osl_codemodel_p codemodel) {
  int high_water_mark = 10 * OSL_MAX_STRING;
  int i;
  char *string = NULL;
  char buffer[OSL_MAX_STRING];
  char *extstring;

  if (codemodel == NULL)
    return NULL;

  OSL_malloc(string, char *, high_water_mark * sizeof(char));
  string[0] = '\0';

  sprintf(buffer, "# Type (0 = loop, 1 = stmt)\n%d\n", codemodel->kind);
  osl_util_safe_strcat(&string, buffer, &high_water_mark);

  if (codemodel->kind == OSL_CODEMODEL_LOOP) {
    sprintf(buffer, "# Coordinates\n%d\n",
            codemodel->u.loop->coordinates != NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    if (codemodel->u.loop->coordinates != NULL) {
      extstring = osl_coordinates_sprint(
          codemodel->u.loop->coordinates);
      osl_util_safe_strcat(&string, extstring, &high_water_mark);
      free(extstring);
    }

    sprintf(buffer, "# Initializer coordinates\n%d\n",
            codemodel->u.loop->initializer_coordinates != NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    if (codemodel->u.loop->initializer_coordinates != NULL) {
      extstring = osl_coordinates_sprint(
          codemodel->u.loop->initializer_coordinates);
      osl_util_safe_strcat(&string, extstring, &high_water_mark);
      free(extstring);
    }

    sprintf(buffer, "# Condition coordinates\n%d\n",
            codemodel->u.loop->condition_coordinates != NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    if (codemodel->u.loop->condition_coordinates != NULL) {
      extstring = osl_coordinates_sprint(
          codemodel->u.loop->condition_coordinates);
      osl_util_safe_strcat(&string, extstring, &high_water_mark);
      free(extstring);
    }

    sprintf(buffer, "# Increment coordinates\n%d\n",
            codemodel->u.loop->increment_coordinates != NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    if (codemodel->u.loop->increment_coordinates != NULL) {
      extstring = osl_coordinates_sprint(
          codemodel->u.loop->increment_coordinates);
      osl_util_safe_strcat(&string, extstring, &high_water_mark);
      free(extstring);
    }
  } else if (codemodel->kind == OSL_CODEMODEL_STMT) {
    sprintf(buffer, "# Coordinates\n%d\n",
            codemodel->u.stmt->coordinates != NULL);
    osl_util_safe_strcat(&string, buffer, &high_water_mark);
    if (codemodel->u.stmt->coordinates != NULL) {
      extstring = osl_coordinates_sprint(
          codemodel->u.stmt->coordinates);
      osl_util_safe_strcat(&string, extstring, &high_water_mark);
      free(extstring);
    }
  }

  sprintf(buffer, "# Children\n%d\n", codemodel->nb_children);
  osl_util_safe_strcat(&string, buffer, &high_water_mark);

  for (i = 0; i < codemodel->nb_children; i++) {
    extstring = osl_codemodel_sprint(codemodel->children[i]);
    if (extstring != NULL) {
      osl_util_safe_strcat(&string, extstring, &high_water_mark);
      free(extstring);
    }
  }

  OSL_realloc(string, char *, (strlen(string) + 1) * sizeof(char));

  return string;
}


/*****************************************************************************
 *                               Reading function                            *
 *****************************************************************************/

/**
 * Reads a codemodel structure from a string complying to the OpenScop textual
 * format and returns a pointer to this structure.  The input parameter is
 * updated to the position in the input string this function reaches
 * immediately after reading the codemodel structure.
 * \param[in,out] input The input string where to find the codemodel.
 *                      Updated to the position after what has been read.
 * \return A pointer to the codemodel structure that has been read.
 */

osl_codemodel_p osl_codemodel_sread(char **input) {
  osl_codemodel_p codemodel;
  int kind, i;

  if (input == NULL || *input == NULL)
    return NULL;

  kind = osl_util_read_int(NULL, input);
  if (kind == OSL_CODEMODEL_LOOP) {
    codemodel = osl_codemodel_create_loop();
    if (osl_util_read_int(NULL, input))
      codemodel->u.loop->coordinates             = osl_coordinates_sread(input);
    if (osl_util_read_int(NULL, input))
      codemodel->u.loop->initializer_coordinates = osl_coordinates_sread(input);
    if (osl_util_read_int(NULL, input))
      codemodel->u.loop->condition_coordinates   = osl_coordinates_sread(input);
    if (osl_util_read_int(NULL, input))
      codemodel->u.loop->increment_coordinates   = osl_coordinates_sread(input);
  } else if (kind == OSL_CODEMODEL_STMT) {
    codemodel = osl_codemodel_create_stmt();
    if (osl_util_read_int(NULL, input))
      codemodel->u.stmt->coordinates = osl_coordinates_sread(input);
  } else {
    codemodel = osl_codemodel_malloc();
  }
  codemodel->nb_children = osl_util_read_int(NULL, input);
  OSL_malloc(codemodel->children, osl_codemodel_p *,
             sizeof(osl_codemodel_p) * codemodel->nb_children);
  for (i = 0; i < codemodel->nb_children; ++i) {
    codemodel->children[i] = osl_codemodel_sread(input);
  }

  return codemodel;
}

/*+***************************************************************************
 *                    Memory allocation/deallocation functions               *
 *****************************************************************************/

/**
 * Allocates the memory space for an osl_codemodel_t structure and sets its
 * fields with default values. Then it returns a pointer to the allocated
 * space.
 * \warning This function is not supposed to be called directly, use
 *          \ref osl_codemodel_create_loop() or \ref osl_codemodel_create_stmt()
 * \return A pointer to an empty codemodel structure with no chlidren and of
 *         \ref OSL_CODEMODEL_UNDEFINED kind.
 */
osl_codemodel_p osl_codemodel_malloc() {
  osl_codemodel_p codemodel;

  OSL_malloc(codemodel, osl_codemodel_p, sizeof(osl_codemodel_t));
  codemodel->kind = OSL_CODEMODEL_UNDEFINED;
  codemodel->nb_children = 0;
  codemodel->children = NULL;

  return codemodel;
}

/**
 * Allocates the memory for a \ref OSL_CODEMODEL_LOOP kind node in the code
 * model and initializes it with zeros, returns it wrapped in
 * \ref osl_codemodel structure instance.
 * \return A pointer to a codemodel structure wrapping a loop structure.
 */
osl_codemodel_p osl_codemodel_create_loop() {
  osl_codemodel_p codemodel;
  osl_codemodel_loop_p loop;

  OSL_malloc(codemodel, osl_codemodel_p, sizeof(osl_codemodel_t));
  OSL_malloc(loop, osl_codemodel_loop_p, sizeof(osl_codemodel_loop_t));
  loop->id = -1;
  loop->coordinates = NULL;
  loop->initializer_coordinates = NULL;
  loop->condition_coordinates = NULL;
  loop->increment_coordinates = NULL;
  codemodel->u.loop = loop;
  codemodel->kind = OSL_CODEMODEL_LOOP;
  codemodel->nb_children = 0;
  codemodel->children = NULL;

  return codemodel;
}

/**
 * Allocates the memory for a \ref OSL_CODEMODEL_STMT kind node in the code
 * model and initializes it with zeros, returns it wrapped in
 * \ref osl_codemodel structure instance.
 * \return A pointer to a codemodel structure wrapping a statement structure.
 */
osl_codemodel_p osl_codemodel_create_stmt() {
  osl_codemodel_p codemodel;
  osl_codemodel_stmt_p stmt;

  OSL_malloc(codemodel, osl_codemodel_p, sizeof(osl_codemodel_t));
  OSL_malloc(stmt, osl_codemodel_stmt_p, sizeof(osl_codemodel_stmt_t));
  stmt->parent_id = -1;
  stmt->coordinates = NULL;
  codemodel->u.stmt = stmt;
  codemodel->kind = OSL_CODEMODEL_STMT;
  codemodel->nb_children = 0;
  codemodel->children = NULL;

  return codemodel;
}

/**
 * Frees the memory allocated for a code model node, including the wrapped
 * statement or loop and all children recursively.
 * \param[in]  A pointer to the codemodel structure to free.
 */
void osl_codemodel_free(osl_codemodel_p codemodel) {
  int i;

  if (codemodel->kind == OSL_CODEMODEL_LOOP) {
    free(codemodel->u.loop);
  } else if (codemodel->kind == OSL_CODEMODEL_STMT) {
    free(codemodel->u.stmt);
  }
  for (i = 0; i < codemodel->nb_children; ++i) {
    osl_codemodel_free(codemodel->children[i]);
  }
  free(codemodel->children);
  free(codemodel);
}


/*+***************************************************************************
 *                            Processing functions                           *
 *****************************************************************************/

/**
 * Appends #child to the list of children of the #codemodel.  The list is
 * automatically enlarged to accommodate the new child.  Ownership of #child is
 * transferred from the caller to #codemodel, it will be automatically freed
 * together with the parent node.
 * \param[in,out] codemodel A pointer to the parent codemodel.
 * \param[in]     child     A pointer to the child codemodel.
 */
void osl_codemodel_add_child(osl_codemodel_p codemodel,
                             osl_codemodel_p child) {
  codemodel->nb_children += 1;
  OSL_realloc(codemodel->children, osl_codemodel_p *,
              sizeof(osl_codemodel_p) * codemodel->nb_children);
  codemodel->children[codemodel->nb_children - 1] = child;
}

/**
 * Removes #child from the list of children of the #codemodel.  The list is
 * automatically shrunk.  Transfers ownership of #child to the caller, it will
 * \b not anymore get freed together with the parent object.  Does nothing if
 * #chlid is not a child node of the #codemodel.
 * \param[in,out] codemodel A pointer to the parent codemodel.
 * \param[in]     child     A pointer to the child codemodel.
 */
void osl_codemodel_remove_child(osl_codemodel_p codemodel,
                                osl_codemodel_p child) {
  int index = -1;
  int i;

  for (i = 0; i < codemodel->nb_children; ++i) {
    if (codemodel->children[i] == child) {
      index = i;
      break;
    }
  }

  for (i = index + 1; i < codemodel->nb_children; ++i) {
    codemodel->children[i - 1] = codemodel->children[i];
  }
  codemodel->nb_children--;
  if (codemodel->nb_children == 0) {
    free(codemodel->children);
    codemodel->children = NULL;
  } else {
    OSL_realloc(codemodel->children, osl_codemodel_p *,
                sizeof(osl_codemodel_p) * codemodel->nb_children);
  }
}

/**
 * Builds and returns a deep copy  of an osl_codemodel_t data structure.
 * \param codemodel The pointer to the codemodel structure to clone.
 * \return A pointer to the copy of the codemodel structure.
 */
osl_codemodel_p osl_codemodel_clone(osl_codemodel_p codemodel) {
  osl_codemodel_p copy;
  osl_codemodel_loop_p loop, copy_loop;
  osl_codemodel_stmt_p stmt, copy_stmt;
  int i;

  OSL_malloc(copy, osl_codemodel_p, sizeof(osl_codemodel_t));
  if (codemodel->kind == OSL_CODEMODEL_STMT) {
    stmt = codemodel->u.stmt;
    OSL_malloc(copy_stmt, osl_codemodel_stmt_p, sizeof(osl_codemodel_stmt_t));
    copy_stmt->parent_id = stmt->parent_id;
    copy_stmt->coordinates = osl_coordinates_clone(stmt->coordinates);

    copy->u.stmt = copy_stmt;
  } else if (codemodel->kind == OSL_CODEMODEL_LOOP) {
    loop = codemodel->u.loop;
    OSL_malloc(copy_loop, osl_codemodel_loop_p, sizeof(osl_codemodel_loop_t));
    copy_loop->id = loop->id;
    copy_loop->coordinates = osl_coordinates_clone(loop->coordinates);
    copy_loop->initializer_coordinates =
        osl_coordinates_clone(loop->initializer_coordinates);
    copy_loop->condition_coordinates =
        osl_coordinates_clone(loop->condition_coordinates);
    copy_loop->increment_coordinates =
        osl_coordinates_clone(loop->increment_coordinates);

    copy->u.loop = copy_loop;
  }
  copy->kind = codemodel->kind;
  copy->nb_children = codemodel->nb_children;
  OSL_malloc(copy->children, osl_codemodel_p *,
             sizeof(osl_codemodel_p) * codemodel->nb_children);
  for (i = 0; i < codemodel->nb_children; ++i) {
    copy->children[i] = osl_codemodel_clone(codemodel->children[i]);
  }
  return copy;
}

/**
 * Checks whether two codemodel structures are equal.  Two codemodel structures
 * are considered equal if they have the same kind, equal coordinates with
 * respect to their kind, and have an equal amount of equal child nodes.
 * \param[in]  first  A codemodel structure to compare.
 * \param[in]  second A codemodel structure to compare to.
 */
int osl_codemodel_equal(osl_codemodel_p first, osl_codemodel_p second) {
  int i;
  int result;

  if (first == second)
    return 1;

  if (first->kind != second->kind)
    return 0;

  if (first->kind == OSL_CODEMODEL_LOOP) {
    if (first->u.loop->id != second->u.loop->id)
      return 0;
    if (!osl_coordinates_equal(first->u.loop->coordinates,
                               second->u.loop->coordinates) ||
        !osl_coordinates_equal(first->u.loop->initializer_coordinates,
                               second->u.loop->initializer_coordinates) ||
        !osl_coordinates_equal(first->u.loop->condition_coordinates,
                               second->u.loop->condition_coordinates) ||
        !osl_coordinates_equal(first->u.loop->increment_coordinates,
                               second->u.loop->increment_coordinates))
      return 0;
  } else if (first->kind == OSL_CODEMODEL_STMT) {
    if (first->u.stmt->parent_id != second->u.stmt->parent_id)
      return 0;
    if (!osl_coordinates_equal(first->u.stmt->coordinates,
                               second->u.stmt->coordinates))
      return 0;
  }

  if (first->nb_children != second->nb_children)
    return 0;
  result = 1;
  for (i = 0; i < first->nb_children && result; ++i) {
    result = result && osl_codemodel_equal(first->children[i],
                                           second->children[i]);
  }

  return result;
}

/**
 * Creates an interface structure corresponding to the codemodel extension and
 * returns it.
 * \return An interface structure for the codemodel extension.
 */
osl_interface_p osl_codemodel_interface() {
  osl_interface_p interface = osl_interface_malloc();

  OSL_strdup(interface->URI, OSL_URI_CODEMODEL);
  interface->idump  = (osl_idump_f)osl_codemodel_idump;
  interface->sprint = (osl_sprint_f)osl_codemodel_sprint;
  interface->sread  = (osl_sread_f)osl_codemodel_sread;
  interface->malloc = (osl_malloc_f)osl_codemodel_malloc;
  interface->free   = (osl_free_f)osl_codemodel_free;
  interface->clone  = (osl_clone_f)osl_codemodel_clone;
  interface->equal  = (osl_equal_f)osl_codemodel_equal;

  return interface;
}

static void osl_codemodel_update_identifiers_r(osl_codemodel_p codemodel,
                                               int *loop_id) {
  int i;

  int current_loop_id = *loop_id;
  int child_loop_id = *loop_id;
  for (i = 0; i < codemodel->nb_children; ++i) {
    if (codemodel->children[i]->kind == OSL_CODEMODEL_LOOP) {
      codemodel->children[i]->u.loop->id = ++child_loop_id;
      osl_codemodel_update_identifiers_r(codemodel->children[i], &child_loop_id);
    } else if (codemodel->children[i]->kind == OSL_CODEMODEL_STMT) {
      codemodel->children[i]->u.stmt->parent_id = current_loop_id;
    }
  }
  *loop_id = child_loop_id;
}

/**
 * Updates identifiers inside the codemodel to make them consistent.  Code model
 * features identifies (\c id for \ref osl_codemodel_loop and \c parent_id for
 * \ref osl_codemodel_stmt) that allow quickly accessing the linear index of
 * the loop or statement in the code.  This function traverses the code model
 * tree in the depth-first order assigning loop identifiers sequentially
 * starting from 0 and updating parent identifiers in the statements
 * respectively.
 * \param[in,out] codemodel A pointer to the codemodel root.
 */
void osl_codemodel_update_identifiers(osl_codemodel_p codemodel) {
  if (codemodel->kind == OSL_CODEMODEL_LOOP) {
    int id = -1;
    codemodel->u.loop->id = -1;
    osl_codemodel_update_identifiers_r(codemodel, &id);
  } else if (codemodel->kind == OSL_CODEMODEL_STMT) {
    codemodel->u.stmt->parent_id = -1;
  }
}

