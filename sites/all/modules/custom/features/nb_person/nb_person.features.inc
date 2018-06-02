<?php
/**
 * @file
 * nb_person.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function nb_person_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function nb_person_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function nb_person_node_info() {
  $items = array(
    'person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('The name, title, photo and biographical info about a person (e.g. staff, team or board member) to display in a list as part of a directory-type page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('Please enter this person\'s name, Last, First.'),
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
