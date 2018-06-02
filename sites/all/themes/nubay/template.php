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
/* -- Delete this line if you want to use these functions
function nubay_preprocess_block(&$vars) {
}
function nubay_process_block(&$vars) {
}
// */


function nubay_preprocess_html(&$vars) {
    
  if (!empty($vars['page']['menu_left']) && !empty($vars['page']['menu_center'])) {
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
  }

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
  }
  
}

