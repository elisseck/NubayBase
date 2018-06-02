<?php
/**
 * @file
 * nb_person.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function nb_person_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_col1|node|person|default';
  $field_group->group_name = 'group_col1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Column 1',
    'weight' => '0',
    'children' => array(
      0 => 'field_person_image',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'Column 1',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-col1 field-group-html-element',
        'element' => 'p',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $field_groups['group_col1|node|person|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_col2|node|person|default';
  $field_group->group_name = 'group_col2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Column 2',
    'weight' => '1',
    'children' => array(
      0 => 'field_person_bio',
      1 => 'group_person_fullname',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'element' => 'div',
        'show_label' => 0,
        'label_element' => 'div',
        'classes' => 'group-col2 field-group-html-element',
        'attributes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_col2|node|person|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_person_fullname|node|person|default';
  $field_group->group_name = 'group_person_fullname';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_col2';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '6',
    'children' => array(
      0 => 'field_person_last_name',
      1 => 'field_person_first_name',
      2 => 'field_person_job_title',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'Name',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-person-fullname field-group-html-element',
        'element' => 'p',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $field_groups['group_person_fullname|node|person|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_person_fullname|node|person|form';
  $field_group->group_name = 'group_person_fullname';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'person';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '1',
    'children' => array(
      0 => 'field_person_last_name',
      1 => 'field_person_first_name',
      2 => 'field_person_job_title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-person-fullname field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_person_fullname|node|person|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Column 1');
  t('Column 2');
  t('Name');

  return $field_groups;
}
