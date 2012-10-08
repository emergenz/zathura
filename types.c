/* See LICENSE file for license and copyright information */

#include <stdlib.h>
#include <girara/datastructures.h>
#include <glib.h>

#include "types.h"
#include "links.h"
#include "internal.h"

zathura_index_element_t*
zathura_index_element_new(const char* title)
{
  if (title == NULL) {
    return NULL;
  }

  zathura_index_element_t* res = g_malloc0(sizeof(zathura_index_element_t));

  res->title = g_strdup(title);

  return res;
}

void
zathura_index_element_free(zathura_index_element_t* index)
{
  if (index == NULL) {
    return;
  }

  g_free(index->title);
  zathura_link_free(index->link);
  g_free(index);
}

zathura_image_buffer_t*
zathura_image_buffer_create(unsigned int width, unsigned int height)
{
  zathura_image_buffer_t* image_buffer = malloc(sizeof(zathura_image_buffer_t));

  if (image_buffer == NULL) {
    return NULL;
  }

  image_buffer->data = calloc(width * height * 3, sizeof(unsigned char));

  if (image_buffer->data == NULL) {
    free(image_buffer);
    return NULL;
  }

  image_buffer->width     = width;
  image_buffer->height    = height;
  image_buffer->rowstride = width * 3;

  return image_buffer;
}

void
zathura_image_buffer_free(zathura_image_buffer_t* image_buffer)
{
  if (image_buffer == NULL) {
    return;
  }

  free(image_buffer->data);
  free(image_buffer);
}

girara_list_t*
zathura_document_information_entry_list_new()
{
  girara_list_t* list = girara_list_new2((girara_free_function_t)
                                         zathura_document_information_entry_free);

  return list;
}

zathura_document_information_entry_t*
zathura_document_information_entry_new(zathura_document_information_type_t type,
                                       const char* value)
{
  if (value == NULL) {
    return NULL;
  }

  zathura_document_information_entry_t* entry =
    g_malloc0(sizeof(zathura_document_information_entry_t));

  entry->type  = type;
  entry->value = g_strdup(value);

  return entry;
}

void
zathura_document_information_entry_free(zathura_document_information_entry_t* entry)
{
  if (entry == NULL) {
    return;
  }

  if (entry->value != NULL) {
    g_free(entry->value);
  }

  g_free(entry);
}
