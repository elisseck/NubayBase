<?php

/**
 * @file
 * A Views field handler for creating an activity.
 */

/**
 * Class views_bulk_civicrm_activity_field_handler_activity_create
 */
class views_bulk_civicrm_activity_field_handler_activity_create  extends views_handler_field {

  /**
   * Builds an array of custom field metadata for a given activity type id
   *
   * @param $activity_type_id
   * @return array
   */
  private function get_custom_field_metadata_for_activity_type($activity_type_id){
    $custom_field_metadata = [];
    if (civicrm_initialize()) {
      $activity_metadata = civicrm_api3('Activity', 'getfields', [
        'sequential' => 1,
        'api_action' => "create",
      ]);
      $types_to_allow = [
        'Select',
        'Select Date',
        'CheckBox',
        'Multi-Select',
        'Radio',
        'Text',
        'TextArea'
      ];
      foreach ($activity_metadata['values'] as $field_metadata) {
        // need to also limit to certain field types here...select, text, number....
        if (strpos($field_metadata['name'], 'custom_') === 0 && in_array($field_metadata['html_type'], $types_to_allow)) {
          $custom_group = civicrm_api3('CustomGroup', 'get', [
            'sequential' => 1,
            'id' => $field_metadata['custom_group_id'],
          ]);
          if (!empty($custom_group['values'][0]['extends_entity_column_value'])) {
            foreach ($custom_group['values'][0]['extends_entity_column_value'] as $at_id) {
              if ($at_id == $activity_type_id ) {
                $custom_field_metadata[$field_metadata['name']] = $field_metadata;
                break;
              }
            }
          }
          else {
            $custom_field_metadata[$field_metadata['name']] = $field_metadata;
          }
        }
      }
    }
    return $custom_field_metadata;
  }

  private function get_fapi_from_metadata($field_metadata, $for_defaults = FALSE) {
    if (empty($field_metadata['is_view'])) {
      $fapi = ['#title' => $field_metadata['label']];
      if (!$for_defaults && !empty($field_metadata['is_required'])) {
        $fapi['#required'] = TRUE;
      }
      switch ($field_metadata['html_type']) {
        case 'Text':
          $fapi['#type'] = 'textfield';
          if (isset($field_metadata['text_length'])) {
            $fapi['#maxlength'] = $field_metadata['text_length'];
          }
          break;
        case 'TextArea':
          $fapi['#type'] = 'textarea';
          break;
        case 'Select':
          $fapi['#type'] = 'select';
          if ($for_defaults) {
            $fapi['#options'] = ['no_default' => 'No Default'] + _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          else {
            $fapi['#options'] = ['use_default' => 'Use Default'] +_views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          break;
        case 'Multi-Select':
          $fapi['#type'] = 'select';
          $fapi['#multiple'] = TRUE;
          if (!$for_defaults) {
            $fapi['#options'] = ['use_default' => 'Use Defaults'] + _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          else {
            $fapi['#options'] = _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }

          break;
        case 'CheckBox':
          $fapi['#type'] = 'checkboxes';
          if (!$for_defaults) {
            $fapi['#options'] = ['use_default' => 'Use Defaults'] + _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          else {
            $fapi['#options'] = _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          break;
        case 'Radio':
          $fapi['#type'] = 'radios';
          if (!$for_defaults) {
            $fapi['#options'] = ['use_default' => 'Use Default'] + _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          else {
            $fapi['#options'] = _views_bulk_civicrm_activity_get_custom_field_value_options($field_metadata['name']);
          }
          break;
        case 'Select Date':
          $fapi['#type'] = 'date_popup';
          $fapi['#date_label_position'] = 'within';
          $fapi['#date_format'] = 'Y-m-d';
          if (!empty($field_metadata['time_format'])) {
            if ($field_metadata['time_format'] == 1) {
              $fapi['#date_format'] .= ' h:i:s a';
            }
            elseif ($field_metadata['time_format'] == 2) {
              $fapi['#date_format'] .= ' G:i:s';
            }
          }
          break;
        default:
          return FALSE;
      }
      return $fapi;
    }
    return [];
  }

  /**
   * @inheritdoc
   */
  function construct() {
    parent::construct();
    $this->additional_fields['id'] = 'id';
  }

  /**
   * @inheritdoc
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * @inheritdoc
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['views_bulk_civicrm_activity_included_custom_fields'] = ['default' => []];
    $options['views_bulk_civicrm_activity_activity_type'] = ['default' => ''];
    return $options;
  }

  /**
   * Creates the form element options for the Views field settings form.
   *
   * @param $form
   * @param $form_state
   */
  function options_form(&$form, &$form_state)
  {
    parent::options_form($form, $form_state);
    $form_state['no_cache'] = FALSE;
    $options = [];
    if (!empty($form_state['values']['options']['views_bulk_civicrm_activity_activity_type'])) {
      $activity_custom_field_options = $this->get_custom_field_metadata_for_activity_type($form_state['values']['options']['views_bulk_civicrm_activity_activity_type']);
      foreach ($activity_custom_field_options as $field_id => $metadata) {
        $options[$field_id] = $metadata['label'];
      }
    }
    elseif (!empty($this->options['views_bulk_civicrm_activity_activity_type'])) {
      $activity_custom_field_options = $this->get_custom_field_metadata_for_activity_type($this->options['views_bulk_civicrm_activity_activity_type']);
      foreach ($activity_custom_field_options as $field_id => $metadata) {
        $options[$field_id] = $metadata['label'];
      }
    }

    $form['views_bulk_civicrm_activity_activity_type'] = [
      '#type' => 'select',
      '#required' => TRUE,
      '#title' => t('Activity Type'),
      '#description' => t('First choose an activity type for the activities that will be created.'),
      '#options' => _views_bulk_civicrm_activity_get_activity_type_options(),
      '#default_value' => $this->options['views_bulk_civicrm_activity_activity_type'],
      '#ajax' => [
        'callback' => 'views_bulk_civicrm_activity_activity_type_ajax_callback',
        'wrapper' => 'views-bulk-civicrm-activity-custom-fields',
      ],
    ];

    $form['views_bulk_civicrm_activity_custom_fields'] = [
      '#type' => 'fieldset',
      '#title' => 'Custom Fields',
      '#collapsible' => FALSE,
      '#prefix' => '<div id="views-bulk-civicrm-activity-custom-fields">',
      '#suffix' => '</div>',
      ];

    if (!empty($this->options['views_bulk_civicrm_activity_activity_type']) || !empty($form_state['values']['options']['views_bulk_civicrm_activity_activity_type'])) {
      $form['views_bulk_civicrm_activity_custom_fields']['help_text'] = [
        '#type'   => 'markup',
        '#markup' => 'Choose which custom fields should be added to the form.',
      ];
      $form['views_bulk_civicrm_activity_custom_fields']['field_selections'] = [
        '#type' => 'checkboxes',
        '#description' => t('Check the boxes next to the custom fields to include'),
        '#options' => $options,
        '#default_value' => $this->options['views_bulk_civicrm_activity_included_custom_fields'],
      ];
    }
  }

  /**
   * Options form submit handler
   *
   * @param $form
   * @param $form_state
   */
  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    $this->options['views_bulk_civicrm_activity_included_custom_fields'] = $form_state['values']['options']['views_bulk_civicrm_activity_custom_fields']['field_selections'];
  }

  /**
   * If the view is using a table style, provide a
   * placeholder for a "select all" checkbox.
   *
   * @return string
   */
  function label() {
    if (!empty($this->view->style_plugin) && $this->view->style_plugin instanceof views_plugin_style_table) {
      return '<!--views-bulk-civicrm-activity-select-all-->';
    }
    else {
      return parent::label();
    }
  }

  /**
   * Render a Views form item placeholder.
   * This causes Views to wrap the View in a form.
   *
   * @param $values
   * @return string
   */
  function render($values) {
    return '<!--form-item-' . $this->options['id'] . '--' . $this->view->row_index . '-->';
  }

  /**
   * Add to and alter the form created by Views.
   *
   * @param $form
   * @param $form_state
   */
  function views_form(&$form, &$form_state) {
    $form['#attached']['css'][] = drupal_get_path('module', 'views_bulk_civicrm_activity') . '/css/views_bulk_civicrm_activity.css';
    $form['#attached']['js'][] = drupal_get_path('module', 'views_bulk_civicrm_activity') . '/js/views_bulk_civicrm_activity.js';
    $class = 'vfaac-views-form';

    $form['#prefix'] = '<div class="' . $class . '">';
    $form['#suffix'] = '</div>';

    // Force browser to reload the page if Back is hit.
    if (!empty($_SERVER['HTTP_USER_AGENT']) && preg_match('/msie/i', $_SERVER['HTTP_USER_AGENT'])) {
      drupal_add_http_header('Cache-Control', 'no-cache'); // works for IE6+
    }
    else {
      drupal_add_http_header('Cache-Control', 'no-store'); // works for Firefox and other browsers
    }

    // only render the form is the activity type has been configured in the Views field settings
    if (!empty($this->options['views_bulk_civicrm_activity_activity_type'])) {
      // fetch custom field metadata for a particular Activity Type
      $form_state['field_metadata'] = $field_metadata = $this->get_custom_field_metadata_for_activity_type($this->options['views_bulk_civicrm_activity_activity_type']);
      // get selected custom fields from Views field configuration
      $selected_fields_settings = $this->options['views_bulk_civicrm_activity_included_custom_fields'];
      // build an array of custom field keys that have been selected in the Views field configuration
      $selected_fields = [];
      foreach ($selected_fields_settings as $id => $value) {
        if (!empty($value)) {
          $selected_fields[] = $id;
        }
      }
      // save it to the form state for use in the submit handler
      $form_state['selected_fields_from_config'] = $selected_fields;

      // activity create date element
      $form['create_date'] = [
        '#title' => t('Create Date'),
        '#type' => 'date_popup',
        '#date_format' => 'Y-m-d H:i:s',
        '#date_year_range' => '-3:+3',
        '#date_label_position' => 'within',
        '#default_value' => date('Y-m-d H:i:s'),
        '#required' => TRUE,
        '#weight' => -4,
      ];

      // subject field
      $form['activity_subject'] = [
        '#type' => 'textfield',
        '#title' => t('Activity Subject'),
        '#weight' => -3,
        '#default_value' => '',
      ];

      // activity status
      // get available status options from CiviCRM
      $activity_status_results = civicrm_api3('Activity', 'getoptions', [
        'sequential' => 1,
        'field' => "activity_status_id",
      ]);

      if (!$activity_status_results['is_error'] && !empty($activity_status_results['values'])) {
        $activity_status_options = ['' => '-CiviCRM Default-'];
        // If there are any found, create a options list consumable by Drupal FAPI
        foreach ($activity_status_results['values'] as $delta => $status_data) {
          $activity_status_options[$status_data['key']] = $status_data['value'];
        }
        // Drupal FAPI activity status form element
        $form['activity_status'] = [
          '#type' => 'select',
          '#title' => t('Activity Status'),
          '#options' => $activity_status_options,
          '#default_value' => '',
          '#weight' => -2,
        ];
      }

      // default value field set
      $form['default_options_section'] = [
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#tree' => TRUE,
        '#weight' => -1,
        '#title' => t('Default Values'),
        '#description' => t('You can optionally choose default values for each configured custom field'),
      ];
      // build fapi for the fields selected in the View field config, for setting default values
      if (!empty($form_state['selected_fields_from_config'])) {
        foreach ($form_state['selected_fields_from_config'] as $field_id) {
          $field_fapi = $this->get_fapi_from_metadata($field_metadata[$field_id], TRUE);
          if (!empty($field_fapi)) {
            $form['default_options_section'][$field_id] = $field_fapi;
          }
        }
      }

      // Create a container for our replacements
      $form[$this->options['id']] = [
        '#type'   => 'container',
        '#tree'   => TRUE,
        '#weight' => 0,
      ];

      // Iterate over the result and add our replacement fields to the form.
      foreach ($this->view->result as $row_index => $row) {
        $form[$this->options['id']][$row_index] = [
          '#type' => 'container',
          '#tree' => TRUE,
          '#prefix' => '<table><tr>',
          '#suffix' => '</tr></table>'
        ];
        $form[$this->options['id']][$row_index]['cid'] = [
          '#type'  => 'value',
          '#value' => $row->id,
        ];
        $form[$this->options['id']][$row_index]['vfaac_select_row'] = [
          '#type' => 'checkbox',
          '#title' => t('Create Activity'),
          '#return_value' => 1,
          //'#theme_wrappers' => [],
          '#attributes'=> ['class' => ['views-bulk-civicrm-activity-select']],
          '#prefix' => '<td>',
          '#suffix' => '</td>',
        ];
        if (!empty($form_state['selected_fields_from_config'])) {
          foreach ($form_state['selected_fields_from_config'] as $field_id) {
            $field_fapi = $this->get_fapi_from_metadata($field_metadata[$field_id]);
            if (!empty($field_fapi)) {
              $form[$this->options['id']][$row_index][$field_id] = $field_fapi;
              $form[$this->options['id']][$row_index][$field_id]['#prefix'] = '<td>';
              $form[$this->options['id']][$row_index][$field_id]['#suffix'] = '</td>';
            }
          }
        }
      }
      $form['#validate'][] = 'views_build_civicrm_activity_views_form_validate';
    }
    else {
      $form['error_message'] = [
        '#type' => 'markup',
        '#markup' => '<p>The Activity Type has not yet been configured in the "Activity Create Form Element" View field settings.</p>'
      ];
    }
  }

  /**
   * Form submit method.
   *
   * @param $form
   * @param $form_state
   */
  function views_form_submit($form, &$form_state)  {
    if (!empty($this->options['views_bulk_civicrm_activity_activity_type'])) {
      // setup the default values array from submitted values from the Default Values fieldset
      $default_values = [];
      foreach ($form_state['selected_fields_from_config'] as $field_id) {
        if (is_array($form_state['values']['default_options_section'][$field_id])) {
          // make sure there are even any user selections for this multi option field
          if (count($form_state['values']['default_options_section'][$field_id])) {
            $default_options_return = [];
            // make sure the selected option id is set to default values array
            foreach ($form_state['values']['default_options_section'][$field_id] as $option_id => $value) {
              // if the checkbox is checked or item selected then option id value to default values array for the field
              if($form_state['field_metadata'][$field_id]['html_type'] == 'CheckBox') {
                if ($value) {
                  $default_options_return[] = $option_id;
                }
              }
              else {
                if ($value || ($option_id == 0 && $value == 0)) {
                  $default_options_return[] = $option_id;
                }
              }
            }
            // if any were selected, then actually add to the default values array for the custom field
            if (count($default_options_return)) {
              $default_values[$field_id] = $default_options_return;
            }
          }
        }
        else {
          if(($form_state['field_metadata'][$field_id]['html_type'] == 'Radio' || $form_state['field_metadata'][$field_id]['html_type'] == 'Select') && isset($form_state['values']['default_options_section'][$field_id]) && $form_state['values']['default_options_section'][$field_id] != 'no_default') {
            $default_values[$field_id] = $form_state['values']['default_options_section'][$field_id];
          }
          elseif ($form_state['field_metadata'][$field_id]['html_type'] == 'Select Date' && isset($form_state['values']['default_options_section'][$field_id]) && is_array($form_state['values']['default_options_section'][$field_id])) {
            $default_values[$field_id] = !empty($form_state['values']['default_options_section'][$field_id]['date']) ? $form_state['values']['default_options_section'][$field_id]['date'] : '';
            $default_values[$field_id] .= !empty($form_state['values']['default_options_section'][$field_id]['time']) ? (' ' . date('H:i:s', strtotime($form_state['values']['default_options_section'][$field_id]['time']))) : '';
            if(empty($default_values[$field_id])) {
              unset($default_values[$field_id]);
            }
          }
          elseif (!empty($form_state['values']['default_options_section'][$field_id]) && $form_state['values']['default_options_section'][$field_id] != 'no_default') {
            $default_values[$field_id] = $form_state['values']['default_options_section'][$field_id];
          }

        }
      }

      // Iterate over the view results.
      foreach ($this->view->result as $row_index => $row) {
        // if this row is checked to create the activity, build the CiviCRM API call parameters and make the call
        if (!empty($form_state['values'][$this->options['id']][$row_index]['vfaac_select_row'])) {
          // basic parameters for every activity
          $params = [
            'sequential' => 1,
            'activity_type_id' => $this->options['views_bulk_civicrm_activity_activity_type'], // activity type configured in Views field config
            'target_id' => $form_state['values'][$this->options['id']][$row_index]['cid'], // cid coming from the row result id property
            'activity_date_time' => $form_state['values']['create_date'], // date selected for create
          ];
          // activity status
          if(isset($form_state['values']['activity_status']) && is_numeric($form_state['values']['activity_status'])) {
            $params['status_id'] = $form_state['values']['activity_status'];
          }
          // activity subject
          if(!empty($form_state['values']['activity_subject'])) {
            $params['subject'] = $form_state['values']['activity_subject'];
          }

          // for each configured field in the Views field settings, process the input into parameter CiviCRM expects...
          foreach ($form_state['selected_fields_from_config'] as $field_id) {
            if (isset($form_state['values'][$this->options['id']][$row_index][$field_id])) {
              // if the form element value is an array, then we have a multi select or multiple checkboxes field...needs special handling
              if (is_array($form_state['values'][$this->options['id']][$row_index][$field_id])) {
                // make sure there are even any user selections for this multi option field
                if (count($form_state['values'][$this->options['id']][$row_index][$field_id])) {
                  $options_return = [];
                  // make sure the selected option id is passed to the API parameters
                  foreach ($form_state['values'][$this->options['id']][$row_index][$field_id] as $option_id => $value) {
                    // if the checkbox is checked or item selected then add to the API parameters
                    if($form_state['field_metadata'][$field_id]['html_type'] == 'CheckBox') {
                      if ($value) {
                        $options_return[] = $option_id;
                      }
                    }
                    else {
                      if ($value || ($option_id == 0 && $value == 0)) {
                        $options_return[] = $option_id;
                      }
                    }
                  }
                  // if any were selected, then actually add to the parameter for the custom field
                  if (count($options_return)) {
                    $params[$field_id] = $options_return;
                  }
                }
              }
              // form element only has one value
              else {
                // if there is no data entered for a Money field, it was creating a 0 value anyway on the Activity...this if clause prevents it....if you wanted a no data entry to cause a 0 value, then remove....
                if ($form_state['field_metadata'][$field_id]['data_type'] == 'Money' && strlen($form_state['values'][$this->options['id']][$row_index][$field_id]) == 0) {
                  if (!empty($default_values[$field_id])) {
                    $params[$field_id] = $default_values[$field_id];
                    continue;
                  }
                  else {
                    // skip if its a money field, and no value entered, and no default value provided
                    continue;
                  }
                }
                // add submitted value to API parameters
                $params[$field_id] = $form_state['values'][$this->options['id']][$row_index][$field_id];
              }
            }
            // populate from default values when appropriate....
            if (isset($default_values[$field_id])) {
              switch ($form_state['field_metadata'][$field_id]['html_type']) {
                case 'Text':
                case 'TextArea':
                case 'Select Date':
                  if(empty($form_state['values'][$this->options['id']][$row_index][$field_id])) {
                    $params[$field_id] = $default_values[$field_id];
                  }
                  break;
                case 'Select':
                case 'Radio':
                  if(!empty($params[$field_id]) && $params[$field_id] == 'use_default') {
                    $params[$field_id] = $default_values[$field_id];
                  }
                  break;
                case 'CheckBox':
                  if(!empty($params[$field_id])) {
                    foreach ($params[$field_id] as $index => $value) {
                      if ($value == 'use_default') {
                        $params[$field_id] = $default_values[$field_id];
                        break;
                      }
                    }
                  }
                  break;
                case 'Multi-Select':
                  if(!empty($params[$field_id])) {
                    foreach ($params[$field_id] as $index => $value) {
                      if (strpos($value, 'use_default') !== FALSE) {
                        $params[$field_id] = $default_values[$field_id];
                        break;
                      }
                    }
                  }
                  break;
              }
            }
            // if there are no default values, and a "use default" option is selected, unset because its giving conflicting commands
            else {
              switch ($form_state['field_metadata'][$field_id]['html_type']) {
                case 'Select':
                case 'Radio':
                  if(!empty($params[$field_id]) && $params[$field_id] == 'use_default') {
                    unset($params[$field_id]);
                  }
                  break;
                case 'CheckBox':
                  if (!empty($params[$field_id])) {
                    foreach ($params[$field_id] as $index => $value) {
                      if ($value == 'use_default') {
                        unset($params[$field_id]);
                        break;
                      }
                    }
                  }
                  break;
                case 'Multi-Select':
                  if (!empty($params[$field_id])) {
                    foreach ($params[$field_id] as $index => $value) {
                      if (strpos($value, 'use_default') !== FALSE) {
                        unset($params[$field_id]);
                        break;
                      }
                    }
                  }
                  break;
              }
            }
          }
          // create the activity with the CiviCRM API
          try {
            $result = civicrm_api3('Activity', 'create', $params);
            drupal_set_message(check_plain('Activity created for contact with contact id:' . $form_state['values'][$this->options['id']][$row_index]['cid']));
          }
          catch (CiviCRM_API3_Exception $e) {
            drupal_set_message($e->getMessage());
            drupal_set_message(check_plain('Error creating activity for contact with contact id:' . $form_state['values'][$this->options['id']][$row_index]['cid']));
          }
        }
      }
    }
    else {
      drupal_set_message('Activity Type not configured on Views Bulk CiviCRM Views field configuration.');
    }
  }
}

/**
 * Validation handler for the Views Bulk CiviCRM Activity Views field handler
 *
 * Handle removing form validation errors for those rows which are not selected to have activities created
 *
 * @param $form
 * @param $form_state
 */
function views_build_civicrm_activity_views_form_validate(&$form, &$form_state) {
  $errors = form_get_errors();
  if (!empty($errors)) {
    // Clear errors.
    form_clear_error();
    // Clear error messages.
    $error_messages = drupal_get_messages('error');
    // Initialize an array where removed error messages are stored.
    $removed_messages = [];

    // filter out any validation errors on rows that are not selected to create an activity
    foreach ($errors as $element_key => $error_message) {
      $key_components = explode('[', $element_key);
      if($key_components[0] = 'activity_create_form_element]') {
        $row_id = $key_components[1][0];
        $field_id = $key_components[2];

        // if the "create activity" checkbox is not checked, then no need to throw a validation error
        // OR if there is a required field, and there is a value in "default values" section for field, then skip the error too,
        if(empty($form_state['values']['activity_create_form_element'][$row_id]['vfaac_select_row']) || !empty($form_state['values']['default_options_section'][$field_id])) {
          $removed_messages[] = $error_message;
          unset($errors[$element_key]);
        }
      }
    }

    // Reinstate remaining errors.
    if(!empty($errors)) {
      foreach ($errors as $name => $error) {
        form_set_error($name, $error);
        // form_set_error() calls drupal_set_message(), so we have to filter out
        // these from the error messages as well.
        $removed_messages[] = $error;
      }
    }

    // Reinstate remaining error messages (which, at this point, are messages that
    // were originated outside of the validation process).
    if(!empty($removed_messages)) {
      $messages_to_show = array_diff($error_messages['error'], $removed_messages);
      if (!empty($messages_to_show)) {
        foreach ($messages_to_show as $message) {
          drupal_set_message($message, 'error');
        }
      }
    }
  }
}

/**
 * Ajax callback for the Views field settings form, Activity Type select list
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function views_bulk_civicrm_activity_activity_type_ajax_callback(&$form, &$form_state) {
  return $form['options']['views_bulk_civicrm_activity_custom_fields'];
}
