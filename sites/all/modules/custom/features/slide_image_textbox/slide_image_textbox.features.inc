<?php
/**
 * @file
 * slide_image_textbox.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function slide_image_textbox_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function slide_image_textbox_node_info() {
  $items = array(
    'slide_image' => array(
      'name' => t('Slide Image Text Box'),
      'base' => 'node_content',
      'description' => t('Images for use with slide show.  Images can included a text box layered on top of image.   Images can also be used as individual blocks.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
