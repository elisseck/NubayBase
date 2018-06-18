(function ($) {
    // Polyfill for jQuery less than 1.6.
    if (typeof $.fn.prop != 'function') {
        jQuery.fn.extend({
            prop: jQuery.fn.attr
        });
    }

    Drupal.behaviors.vfaac = {
        attach: function(context) {
            $('.vfaac-views-form', context).each(function() {
                Drupal.vfaac.initTableBehaviors(this);
               // Drupal.vfaac.initGenericBehaviors(this);
            });
        }
    }

    Drupal.vfaac = Drupal.vfaac || {};
    Drupal.vfaac.initTableBehaviors = function(form) {
        // This is the "select all" checkbox in (each) table header.
        $('.views-bulk-civicrm-activity-select-all', form).click(function() {
            var table = $(this).closest('table')[0];
            $('.views-bulk-civicrm-activity-select:not(:disabled)', table).prop('checked', this.checked);
        });

        $('.views-bulk-civicrm-activity-select', form).click(function() {
            var table = $(this).closest('table.views-table')[0];
            if (!this.checked) {
                $('.views-bulk-civicrm-activity-select-all', table).prop('checked', false);
            }
        });
    }

   Drupal.vfaac.initGenericBehaviors = function(form) {

   }

})(jQuery);