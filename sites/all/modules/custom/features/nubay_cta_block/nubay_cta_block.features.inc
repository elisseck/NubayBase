<?php
/**
 * @file
 * nubay_cta_block.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nubay_cta_block_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function nubay_cta_block_node_info() {
  $items = array(
    'cta_block' => array(
      'name' => t('CTA Block'),
      'base' => 'node_content',
      'description' => t('"Call to Action" block presented as a clickable block or with clickable text.'),
      'has_title' => '1',
      'title_label' => t('CTA Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
