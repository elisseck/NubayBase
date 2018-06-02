<?php
/**
 * @file
 * nb_slices_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nb_slices_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function nb_slices_page_node_info() {
  $items = array(
    'slices_page' => array(
      'name' => t('Slices Page (NB)'),
      'base' => 'node_content',
      'description' => t('Page that is  created using vertical "slices" with image and text options for layout.   This content type is only styled for use with Nubay theme.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
