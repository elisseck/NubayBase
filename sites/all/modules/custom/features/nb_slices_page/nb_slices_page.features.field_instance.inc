<?php
/**
 * @file
 * nb_slices_page.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function nb_slices_page_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-slices_page-field_add_slices'.
  $field_instances['node-slices_page-field_add_slices'] = array(
    'bundle' => 'slices_page',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'paragraphs',
        'settings' => array(
          'view_mode' => 'full',
        ),
        'type' => 'paragraphs_view',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'no_wrapper',
    'field_name' => 'field_add_slices',
    'label' => 'Slice',
    'readmore_behaviour' => 'default',
    'required' => 0,
    'settings' => array(
      'add_mode' => 'button',
      'allowed_bundles' => array(
        'slice_combo_img_over_text' => 'slice_combo_img_over_text',
        'slice_combo_text_img_LR' => 'slice_combo_text_img_LR',
        'slice_container_multi_cols' => 'slice_container_multi_cols',
        'slice_image_textbox' => 'slice_image_textbox',
        'slice_img_fwidth' => 'slice_img_fwidth',
        'slice_text' => 'slice_text',
      ),
      'bundle_weights' => array(
        'slice_combo_img_over_text' => -9,
        'slice_combo_text_img_LR' => -8,
        'slice_container_multi_cols' => -6,
        'slice_image_textbox' => 5,
        'slice_img_fwidth' => -10,
        'slice_text' => -7,
      ),
      'default_edit_mode' => 'open',
      'title' => 'Slice',
      'title_multiple' => 'Slices',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'paragraphs',
      'settings' => array(),
      'type' => 'paragraphs_embed',
      'weight' => 43,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Slice');

  return $field_instances;
}
