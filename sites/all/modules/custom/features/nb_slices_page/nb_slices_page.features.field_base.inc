<?php
/**
 * @file
 * nb_slices_page.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function nb_slices_page_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_add_slices'.
  $field_bases['field_add_slices'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_add_slices',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  return $field_bases;
}
