<?php

/**
 * @file
 * Template.php - process theme data for your sub-theme.
 * 
 * Rename each function and instance of "footheme" to match
 * your subthemes name, e.g. if you name your theme "footheme" then the function
 * name will be "footheme_preprocess_hook". Tip - you can search/replace
 * on "footheme".
 */


/**
 * Override or insert variables for the html template.
 */
/* -- Delete this line if you want to use this function
function nubay_preprocess_html(&$vars) {
}
function nubay_process_html(&$vars) {
}
// */


/**
 * Override or insert variables for the page templates.
 */
/* -- Delete this line if you want to use these functions
function nubay_preprocess_page(&$vars) {
}
function nubay_process_page(&$vars) {
}
// */


/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function nubay_preprocess_node(&$vars) {
}
function nubay_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function nubay_preprocess_comment(&$vars) {
}
function nubay_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
function nubay_preprocess_block(&$vars) {
  if (module_exists('style_library_entity')) {
    $superfish_extension_enabled = theme_get_setting('nubay_superfish_enable');
    if (!empty($superfish_extension_enabled)) {
      if (strpos($vars['block_html_id'], 'superfish') !== FALSE) {
        $style_library_id = theme_get_setting('nubay_superfish_style_library');
        if (!empty($style_library_id)) {
          try {
            $style_library = entity_load_single('style_library_entity', $style_library_id);
            if (!empty($style_library->enabled)) {
              // load css file
              if (!empty($style_library->field_style_library_css['und'])) {
                foreach ($style_library->field_style_library_css['und'] as $delta => $css_file) {
                  $path = file_create_url($css_file['uri']);
                  drupal_add_css($path,
                    [
                      'group'      => CSS_THEME,
                      'media'      => 'screen',
                      'preprocess' => FALSE,
                      'weight'     => '9998',
                    ]);
                }
              }
              // add css from Additional CSS text field..
              if (!empty($style_library->field_style_library_add_css['und'][0]['value'])) {
                drupal_add_css($style_library->field_style_library_add_css['und'][0]['value'],
                  [
                    'group'      => CSS_THEME,
                    'type'       => 'inline',
                    'media'      => 'screen',
                    'preprocess' => FALSE,
                    'weight'     => '9999',
                  ]);
              }
            }
          }
          catch (Exception $e) {
            watchdog('nubay_theme_extension', $e->getMessage());
          }
        }
      }
    }
  }
}

/*
function nubay_process_block(&$vars) {
}
*/


function nubay_preprocess_html(&$vars) {
    
  /*if (!empty($vars['page']['menu_left']) && !empty($vars['page']['menu_center'])) {
      $vars['classes_array'][] = 'menu_left';
  }
  
  if (!empty($vars['page']['menu_left']) && !empty($vars['page']['menu_right'])) {
      $vars['classes_array'][] = 'both_menu';
  }
  
  if (!empty($vars['page']['menu_left']) && !empty($vars['page']['menu_center'] && !empty($vars['page']['menu_right']))) {
     $vars['classes_array'][] = 'menu_center';
  }
  
  if (!empty($vars['page']['menu_center']) && !empty($vars['page']['menu_right'])) {
      $vars['classes_array'][] = 'menu_right';
  }

  if (!empty($vars['page']['footer_left']) && !empty($vars['page']['footer_center'])) {
      $vars['classes_array'][] = 'footer_left';
  }
  
  if (!empty($vars['page']['footer_left']) && !empty($vars['page']['footer_right'])) {
      $vars['classes_array'][] = 'both_footer';
  }
  
  if (!empty($vars['page']['footer_left']) && !empty($vars['page']['footer_center'] && !empty($vars['page']['footer_right']))) {
     $vars['classes_array'][] = 'footer_center';
  }
  
  if (!empty($vars['page']['footer_center']) && !empty($vars['page']['footer_right'])) {
      $vars['classes_array'][] = 'footer_right';
  }*/

  global $theme_key;
  $theme_name = $theme_key;
  if (at_get_setting('enable_extensions', $theme_name) == 1) {
    // Get the path to the directory where our CSS files are saved
    $path = variable_get('theme_' . $theme_name . '_files_directory');

    // Load the themestyles CSS from public files
    $filepath = $path . '/' . $theme_name . '.themestyles.css';
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }

    // load the inlineblock styles
    $filepath = $path . '/' . $theme_name . '.inlineblock-styles.css';
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }

    // load the Block Margins styles
    $filepath = $path . '/' . $theme_name . '.blockmargins-styles.css';
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }

    // load menu/footer regions inline styles
    $filepath = $path . '/' . $theme_name . '.inlineregions-styles.css';
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }

    // superfish menu styles
    $filepath = $path . '/' . $theme_name . '.superfish-styles.css';
    if (file_exists($filepath)) {
      drupal_add_css($filepath, array(
          'preprocess' => TRUE,
          'group' => CSS_THEME,
          'media' => 'screen',
          'every_page' => TRUE,
        )
      );
    }
    else {
      at_load_failure($filepath, $theme_name);
    }
  }
  
}

