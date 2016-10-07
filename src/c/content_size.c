#include <pebble.h>

static Window *s_window;
static TextLayer *s_text_layer;
static PreferredContentSize s_content_size;

static void prv_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(s_window);
  GRect bounds = layer_get_bounds(window_layer);

  s_text_layer = text_layer_create((GRect) { .origin = { 0, 50 }, .size = { bounds.size.w, 80 } });
  text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);

  // Change font size based on ContentSize
  switch(s_content_size) {
    case PreferredContentSizeSmall:
      text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD));
      text_layer_set_text(s_text_layer, "Content Size\nSmall");
      break;
    case PreferredContentSizeMedium:
      text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
      text_layer_set_text(s_text_layer, "Content Size\nMedium");
      break;
    case PreferredContentSizeLarge:
      text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
      text_layer_set_text(s_text_layer, "Content Size\nLarge");
      break;
    case PreferredContentSizeExtraLarge:
      text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
      text_layer_set_text(s_text_layer, "Content Size\nExtra Large");
      break;
    default:
      break;
  }

  layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void prv_window_unload(Window *window) {
  text_layer_destroy(s_text_layer);
}

static void prv_init(void) {
  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .load = prv_window_load,
    .unload = prv_window_unload,
  });

  // Detect ContentSize setting
  s_content_size = preferred_content_size();

  window_stack_push(s_window, true);
}

static void prv_deinit(void) {
  window_destroy(s_window);
}

int main(void) {
  prv_init();
  app_event_loop();
  prv_deinit();
}
