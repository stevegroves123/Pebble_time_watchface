//*************************//
//* Pebble Time Watchface *//
//*  by Steve Groves      *//
//*     May 2015          *//
//*************************//

#include <pebble.h>
#define COLOUR_INVERT 0

  // Create a long-lived buffers
static char time_buffer[] = "00:00";
static char year[] = "0000 ";
static char date[] = " 00/00";
static char pebs[] = " Pebble";
static char pebtime[] = "time ";
static bool flag = false;

  // Create static text_layers
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_messageyear_layer;
static TextLayer *s_messagedate_layer;


  // Routine to update time/date variables
static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into the buffer
  if(clock_is_24h_style() == true) {
    // Use 24 hour format
    strftime(time_buffer, sizeof("00:00"), "%H:%M", tick_time);
  } else {
    // Use 12 hour format
    strftime(time_buffer, sizeof("00:00"), "%I:%M", tick_time);
  }

  // Display the date in day/month format
  strftime(date, sizeof(" 00/00"), " %d/%m", tick_time);
  strftime(year, sizeof("0000 "), "%Y ", tick_time);
  
  if(flag==true)
    {
      // Display this time on the TextLayer
      text_layer_set_text(s_time_layer, time_buffer);  
      text_layer_set_text(s_messageyear_layer, pebtime);
      text_layer_set_text(s_messagedate_layer, pebs);
  }
  else {
      // Display this time on the TextLayer
      text_layer_set_text(s_time_layer, time_buffer);
      text_layer_set_text(s_messageyear_layer, year);
      text_layer_set_text(s_messagedate_layer, date);
  }
}


static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}


static void main_window_load(Window *window)
  {
  
  int8_t inverted = persist_read_int(COLOUR_INVERT);
  
  s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
    
  if(inverted != 5)
    {
      s_messagedate_layer = text_layer_create(GRect (0, 0, 144, 50));
      text_layer_set_font(s_messagedate_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
      text_layer_set_text_color(s_messagedate_layer, GColorBlack);
      text_layer_set_text_alignment(s_messagedate_layer, GTextAlignmentLeft);
    
      s_messageyear_layer = text_layer_create(GRect (0, 120, 144, 50)); 
      text_layer_set_font(s_messageyear_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
      text_layer_set_text_color(s_messageyear_layer, GColorBlack);
      text_layer_set_text_alignment(s_messageyear_layer, GTextAlignmentRight);
    
      flag = false;      
  }
  else if(inverted == 5)
    {
      s_messagedate_layer = text_layer_create(GRect (0, 0, 144, 50));
      text_layer_set_font(s_messagedate_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
      text_layer_set_text_color(s_messagedate_layer, GColorWhite);
      text_layer_set_background_color(s_messagedate_layer, GColorBlack);
      text_layer_set_text(s_messagedate_layer, pebs);
      text_layer_set_text_alignment(s_messagedate_layer, GTextAlignmentLeft);
  
      s_messageyear_layer = text_layer_create(GRect (0, 120, 144, 50)); 
      text_layer_set_font(s_messageyear_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28));
      text_layer_set_text_color(s_messageyear_layer, GColorWhite);
      text_layer_set_background_color(s_messageyear_layer, GColorBlack);
      text_layer_set_text(s_messageyear_layer, pebtime);
      text_layer_set_text_alignment(s_messageyear_layer, GTextAlignmentRight);
    
     flag = true;
  }
  //Option-specific setup
  if(inverted == 1)
    {
        //Set colour to blue
        text_layer_set_text_color(s_messageyear_layer, GColorWhite);
        text_layer_set_background_color(s_messageyear_layer, GColorBlue);
        text_layer_set_text_color(s_messagedate_layer, GColorWhite);
        text_layer_set_background_color(s_messagedate_layer, GColorBlue); 
        flag = false;
  }
  else if (inverted == 2)
    {
        //Set colout to red
        text_layer_set_text_color(s_messageyear_layer, GColorWhite);
        text_layer_set_background_color(s_messageyear_layer, GColorRed);
        text_layer_set_text_color(s_messagedate_layer, GColorWhite);
        text_layer_set_background_color(s_messagedate_layer, GColorRed);
        flag = false;
  }
  else if (inverted == 3)
    {
        //Set colour to green
        text_layer_set_text_color(s_messageyear_layer, GColorBlack);
        text_layer_set_background_color(s_messageyear_layer, GColorGreen);
        text_layer_set_text_color(s_messagedate_layer, GColorBlack);
        text_layer_set_background_color(s_messagedate_layer, GColorGreen);  
        flag = false;
  }
  else if (inverted == 4)
    {
        //Set colout to yellow
        text_layer_set_text_color(s_messageyear_layer, GColorBlack);
        text_layer_set_background_color(s_messageyear_layer, GColorYellow);
        text_layer_set_text_color(s_messagedate_layer, GColorBlack); 
        text_layer_set_background_color(s_messagedate_layer, GColorYellow);
        flag = false;
  }
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_messageyear_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_messagedate_layer));
}

static void main_window_unload(Window *window)
  {
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_messageyear_layer);
  text_layer_destroy(s_messagedate_layer);
}

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  //Get Tuple
  Tuple *t = dict_read_first(iterator);
  if(t)
  {
    switch(t->key)
    {
    case COLOUR_INVERT:
      //It's the COLOUR_INVERT key
      if(strcmp(t->value->cstring, "b") == 0)
      {
        //Set colour to blue
        text_layer_set_text_color(s_messageyear_layer, GColorWhite);
        text_layer_set_background_color(s_messageyear_layer, GColorBlue);
        text_layer_set_text_color(s_messagedate_layer, GColorWhite);
        text_layer_set_background_color(s_messagedate_layer, GColorBlue); 
        flag = false;
        persist_write_int(COLOUR_INVERT, 1);
      }
      else if(strcmp(t->value->cstring, "r") == 0)
      {
        //Set colout to red
        text_layer_set_text_color(s_messageyear_layer, GColorWhite);
        text_layer_set_background_color(s_messageyear_layer, GColorRed);
        text_layer_set_text_color(s_messagedate_layer, GColorWhite);
        text_layer_set_background_color(s_messagedate_layer, GColorRed);
        flag = false;        
        persist_write_int(COLOUR_INVERT, 2);
      }
      else if(strcmp(t->value->cstring, "g") == 0)
      {
        //Set colour to green
        text_layer_set_text_color(s_messageyear_layer, GColorBlack);
        text_layer_set_background_color(s_messageyear_layer, GColorGreen);
        text_layer_set_text_color(s_messagedate_layer, GColorBlack);
        text_layer_set_background_color(s_messagedate_layer, GColorGreen);
        flag = false;        
        persist_write_int(COLOUR_INVERT, 3);
      }
      else if(strcmp(t->value->cstring, "y") == 0)
      {
        //Set colout to white
        text_layer_set_text_color(s_messageyear_layer, GColorBlack);
        text_layer_set_background_color(s_messageyear_layer, GColorYellow);
        text_layer_set_text_color(s_messagedate_layer, GColorBlack);
        text_layer_set_background_color(s_messagedate_layer, GColorYellow);
        flag = false;        
        persist_write_int(COLOUR_INVERT, 4);
      }
      else if(strcmp(t->value->cstring, "x") == 0)
      {
        //Set colour to black and display "Pebble" "time" 
        text_layer_set_text_color(s_messageyear_layer, GColorWhite);
        text_layer_set_background_color(s_messageyear_layer, GColorBlack);
        text_layer_set_text_color(s_messagedate_layer, GColorWhite);
        text_layer_set_background_color(s_messagedate_layer, GColorBlack);
        // Set layer's to display the text "Pebble" and "time"
        text_layer_set_text(s_messageyear_layer, pebtime);
        text_layer_set_text(s_messagedate_layer, pebs);
        flag = true;       
        persist_write_int(COLOUR_INVERT, 5);
      }
      break;
    }
  }
}

static void init()
  {
  s_main_window = window_create();
  window_set_window_handlers(s_main_window, (WindowHandlers)
                             {
                               .load = main_window_load,
                               .unload = main_window_unload 
                             });
  window_stack_push(s_main_window, true);
  
  // Make sure the time is displayed from the start
  update_time();
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);  
  
  // do something with the feedback from the phone
  app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit()
  {
  window_destroy(s_main_window);
}

int main(void)
  {
  init();
  app_event_loop();
  deinit();
}