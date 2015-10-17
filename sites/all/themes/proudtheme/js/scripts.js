
(function($, Drupal) {
  Drupal.behaviors.helm_base = {
    attach: function(context, settings) {
      // Open external links in new window
      var reg = new RegExp("/" + window.location.host + "/");
      $("a").each(function() {
        if (!reg.test(this.href)) {
          $(this).attr('target', '_blank');
        }
      });

      // Run height equalizer
      $('[data-equalizer]').equalizeHeight();
    }
  };
})(jQuery, Drupal);
