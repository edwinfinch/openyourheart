#include <pebble.h>

Window *window;
TextLayer *time_layer;
TextLayer *background;
InverterLayer *invert;
static GFont hand_written; 

GBitmap *heart_bottom;
BitmapLayer *heart_bottom_layer;
GBitmap *heart_top;
BitmapLayer *heart_top_layer;
GBitmap *arrow;
BitmapLayer *arrow_layer;

char time_buffer[] = "00:00";

static bool boot = false;
static int animationNumber = 0;

void on_animation_stopped(Animation *anim, bool finished, void *context)
{
    //Free the memory used by the Animation
    property_animation_destroy((PropertyAnimation*) anim);
	animationNumber++;
	
	if(animationNumber > 4){
		boot = false;
	}
}
 
void animate_layer(Layer *layer, GRect *start, GRect *finish, int duration, int delay)
{
    PropertyAnimation *anim = property_animation_create_layer_frame(layer, start, finish);

    animation_set_duration((Animation*) anim, duration);
    animation_set_delay((Animation*) anim, delay);
     
    AnimationHandlers handlers = {
        .stopped = (AnimationStoppedHandler) on_animation_stopped
    };
    animation_set_handlers((Animation*) anim, handlers, NULL);
     
    //Start animation
    animation_schedule((Animation*) anim);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed){
	//How the watch handles second ticks
	strftime(time_buffer, sizeof("00:00"), "%H:%M", tick_time);
	//24hr or 12hr, checks and updates accordingly
	if(clock_is_24h_style()){
      strftime(time_buffer, sizeof(time_buffer), "%H:%M", tick_time);
    }
    else{
      strftime(time_buffer,sizeof(time_buffer),"%I:%M",tick_time);
    }
	//Update time
	text_layer_set_text(time_layer, time_buffer);
	
	int seconds = tick_time->tm_sec;
	
	if(seconds == 58 && boot == false)
	{
	  GRect startFalse = GRect(-200, -12, 144, 168);
	  GRect finishFalse = GRect(-199, -12, 144, 168);
	  GRect start11 = GRect(5, 53, 168, 144);
	  GRect finish11 = GRect(250, 53, 168, 144);
	  GRect start2 = GRect(-200, -12, 144, 168);
	  GRect finish2 = GRect(250, -12, 144, 168);
	  GRect start3 = GRect(0, 35, 144, 168);
	  GRect finish3 = GRect(0, 70, 144, 168);
	  GRect start4 = GRect(0, -49, 144, 168);
	  GRect finish4 = GRect(0, -74, 144, 168);
	  animate_layer(bitmap_layer_get_layer(arrow_layer), &startFalse, &finishFalse, 2, 2);
	  animate_layer(bitmap_layer_get_layer(arrow_layer), &start2, &finish2, 1000, 700);
	  animate_layer(text_layer_get_layer(time_layer), &start11, &finish11, 600, 1010);
	  animate_layer(bitmap_layer_get_layer(heart_bottom_layer), &start3, &finish3, 1000, 0);
	  animate_layer(bitmap_layer_get_layer(heart_top_layer), &start4, &finish4, 1000, 0);
		
	
	  GRect start = GRect(-200, 53, 144, 168);
	  GRect finish = GRect(-8, 53, 140, 168);
	  GRect start1 = GRect(-200, -12, 144, 168);
	  GRect finish1 = GRect(5, -12, 144, 168);
	  GRect start21 = GRect(5, -12, 144, 168);
	  GRect finish21 = GRect(-200, -12, 144, 168);
	  GRect start31 = GRect(0, 70, 144, 168);
	  GRect finish31 = GRect(0, 35, 144, 168);
	  GRect start41 = GRect(0, -74, 144, 168);
	  GRect finish41 = GRect(0, -49, 144, 168);
	  animate_layer(bitmap_layer_get_layer(arrow_layer), &start1, &finish1, 1000, 2100);
	  animate_layer(text_layer_get_layer(time_layer), &start, &finish, 1000, 2020);
	  animate_layer(bitmap_layer_get_layer(arrow_layer), &start21, &finish21, 1000, 3120);
	  animate_layer(bitmap_layer_get_layer(heart_bottom_layer), &start31, &finish31, 1000, 4100);
	  animate_layer(bitmap_layer_get_layer(heart_top_layer), &start41, &finish41, 1000, 4100);
	}
	
}

void window_load(Window *window){
	Layer *window_layer = window_get_root_layer(window);
	//Define custom font
	hand_written = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CUCUMBERS_35));
	
	//Black background
	background = text_layer_create(GRect(0,0,144,168));
	text_layer_set_background_color(background, GColorBlack);
	layer_add_child(window_get_root_layer(window), (Layer*) background);
	
	//Heart bottom layer
	heart_bottom = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HEART_BOTTOM_BLACK);
	heart_bottom_layer = bitmap_layer_create(GRect(0,70,144,168));
	bitmap_layer_set_background_color(heart_bottom_layer, GColorClear);
	bitmap_layer_set_bitmap(heart_bottom_layer, heart_bottom);
	layer_add_child(window_layer, bitmap_layer_get_layer(heart_bottom_layer));
	
	//Heart top layer
	heart_top = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HEART_TOP_BLACK);
	heart_top_layer = bitmap_layer_create(GRect(0,-74,144,168));
	bitmap_layer_set_background_color(heart_top_layer, GColorClear);
	bitmap_layer_set_bitmap(heart_top_layer, heart_top);
	layer_add_child(window_layer, bitmap_layer_get_layer(heart_top_layer));
	
	//Arrow layer (set up, don't show)
	arrow = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ARROW);
	arrow_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
	bitmap_layer_set_bitmap(arrow_layer, arrow);
	layer_add_child(window_layer, bitmap_layer_get_layer(arrow_layer));
	
	//Time layer (with custom font)
  	time_layer = text_layer_create(GRect(5, 53, 140, 168));
  	text_layer_set_background_color(time_layer, GColorClear);
  	text_layer_set_text_color(time_layer, GColorWhite);
  	text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  	text_layer_set_font(time_layer, hand_written);    
  	layer_add_child(window_get_root_layer(window), (Layer*) time_layer);
	
	//Invert pixels 
	//invert = inverter_layer_create(GRect(0,0,144,168));
	//layer_add_child(window_get_root_layer(window), (Layer*) invert);
	
	//Load structure
	struct tm *t;
  	time_t temp;        
  	temp = time(NULL);        
  	t = localtime(&temp); 
	
	tick_handler(t, MINUTE_UNIT);
}

void window_unload(Window *window){
	//Destroy resources
	//Like a good developer would
	text_layer_destroy(time_layer);
	text_layer_destroy(background);
	inverter_layer_destroy(invert);
	fonts_unload_custom_font(hand_written);
	gbitmap_destroy(heart_bottom);
	gbitmap_destroy(heart_top);
	bitmap_layer_destroy(heart_bottom_layer);
	bitmap_layer_destroy(heart_top_layer);
}

void handle_init(void) {
	  window = window_create();
	  window_set_window_handlers(window, (WindowHandlers) {
  		.load = window_load,
  		.unload = window_unload,
      });
	  tick_timer_service_subscribe(SECOND_UNIT, (TickHandler) tick_handler);
	  time_layer = text_layer_create(GRect(0, 0, 144, 168));
	  window_stack_push(window, true);
	
	  boot = true;
	
	  GRect start = GRect(-200, 53, 144, 168);
	  GRect finish = GRect(5, 53, 144, 168);
	  GRect start1 = GRect(-200, -12, 144, 168);
	  GRect finish1 = GRect(5, -12, 144, 168);
	  GRect start2 = GRect(5, -12, 144, 168);
	  GRect finish2 = GRect(-200, -12, 144, 168);
	  GRect start3 = GRect(0, 70, 144, 168);
	  GRect finish3 = GRect(0, 35, 144, 168);
	  GRect start4 = GRect(0, -74, 144, 168);
	  GRect finish4 = GRect(0, -49, 144, 168);
	  animate_layer(bitmap_layer_get_layer(arrow_layer), &start1, &finish1, 1000, 10);
	  animate_layer(text_layer_get_layer(time_layer), &start, &finish, 1000, 10);
	  animate_layer(bitmap_layer_get_layer(arrow_layer), &start2, &finish2, 1000, 1010);
	  animate_layer(bitmap_layer_get_layer(heart_bottom_layer), &start3, &finish3, 1000, 2100);
	  animate_layer(bitmap_layer_get_layer(heart_top_layer), &start4, &finish4, 1000, 2100);
	  
}

void handle_deinit(void) {
	  tick_timer_service_unsubscribe();
	  animation_unschedule_all();
	  window_destroy(window);
}

int main(void) {
	  handle_init();
	  app_event_loop();
	  handle_deinit();
}
