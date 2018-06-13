<?php

/**
 * @file
 * Views file for Views Bulk CiviCRM Activity
 */

/**
 * Implements hook_views_data_alter().
 *
 * @param $data
 *   Information about Views' tables and fields.
 */
function views_bulk_civicrm_activity_views_data_alter(&$data) {
  // Add the Title form field to
  $data['civicrm_contact']['activity_create_form_element'] = array(
    'field' => array(
      'title' => t('Activity Create Form Element'),
      'help' => t('Enter custom field values for the created activity'),
      'handler' => 'views_bulk_civicrm_activity_field_handler_activity_create',
    ),
  );
}

