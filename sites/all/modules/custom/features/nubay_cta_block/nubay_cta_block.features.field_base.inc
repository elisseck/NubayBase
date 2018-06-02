<?php
/**
 * @file
 * nubay_cta_block.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function nubay_cta_block_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_background_color'.
  $field_bases['field_background_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_background_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'allow_empty' => 1,
      'palette' => '',
      'show_buttons' => 1,
      'show_input' => 1,
      'show_palette' => 0,
      'show_palette_only' => 0,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  // Exported field_base: 'field_background_image'.
  $field_bases['field_background_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_background_image',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'uri_scheme' => 'public',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  // Exported field_base: 'field_block_height'.
  $field_bases['field_block_height'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_block_height',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_block_width'.
  $field_bases['field_block_width'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_block_width',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_border_color'.
  $field_bases['field_border_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_border_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'allow_empty' => 1,
      'palette' => '',
      'show_buttons' => 1,
      'show_input' => 1,
      'show_palette' => 0,
      'show_palette_only' => 0,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  // Exported field_base: 'field_border_radius'.
  $field_bases['field_border_radius'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_border_radius',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_border_width'.
  $field_bases['field_border_width'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_border_width',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_cta_block_padding_right'.
  $field_bases['field_cta_block_padding_right'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cta_block_padding_right',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_cta_block_padding_top'.
  $field_bases['field_cta_block_padding_top'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cta_block_padding_top',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_cta_link_text'.
  $field_bases['field_cta_link_text'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cta_link_text',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_hide_title'.
  $field_bases['field_hide_title'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_hide_title',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => 'Hide title',
      ),
      'allowed_values_function' => '',
      'allowed_values_php' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_link_destination'.
  $field_bases['field_link_destination'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link_destination',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'link',
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ),
    'translatable' => 0,
    'type' => 'link_field',
  );

  // Exported field_base: 'field_link_font_typeface'.
  $field_bases['field_link_font_typeface'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link_font_typeface',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Georgia, \'Times New Roman\', Times, serif' => 'Georgia, \'Times New Roman\', Times, serif',
        'Verdana, Arial, Helvetica, sans-serif' => 'Verdana, Arial, Helvetica, sans-serif',
        'Arial, Helvetica, sans-serif' => 'Arial, Helvetica, sans-serif',
      ),
      'allowed_values_function' => '',
      'allowed_values_php' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  // Exported field_base: 'field_link_text_color'.
  $field_bases['field_link_text_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link_text_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'allow_empty' => 1,
      'palette' => '',
      'show_buttons' => 1,
      'show_input' => 1,
      'show_palette' => 0,
      'show_palette_only' => 0,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  // Exported field_base: 'field_link_text_size'.
  $field_bases['field_link_text_size'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_link_text_size',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_padding'.
  $field_bases['field_padding'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_padding',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 2,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_title_text_font_color'.
  $field_bases['field_title_text_font_color'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_title_text_font_color',
    'indexes' => array(
      'rgb' => array(
        0 => 'rgb',
      ),
    ),
    'locked' => 0,
    'module' => 'color_field',
    'settings' => array(
      'allow_empty' => 1,
      'palette' => '',
      'show_buttons' => 1,
      'show_input' => 1,
      'show_palette' => 0,
      'show_palette_only' => 0,
    ),
    'translatable' => 0,
    'type' => 'color_field_rgb',
  );

  // Exported field_base: 'field_title_text_font_size'.
  $field_bases['field_title_text_font_size'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_title_text_font_size',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_title_text_font_typeface'.
  $field_bases['field_title_text_font_typeface'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_title_text_font_typeface',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'Georgia, \'Times New Roman\', Times, serif' => 'Georgia, \'Times New Roman\', Times, serif',
        'Verdana, Arial, Helvetica, sans-serif' => 'Verdana, Arial, Helvetica, sans-serif',
        'Arial, Helvetica, sans-serif' => 'Arial, Helvetica, sans-serif',
      ),
      'allowed_values_function' => '',
      'allowed_values_php' => '',
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
