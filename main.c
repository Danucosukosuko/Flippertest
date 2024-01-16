// Archivo: main.c
#include <furi.h>
#include <furi-hal.h>
#include <gui/gui.h>
#include <gui/view.h>
#include <gui/view_port.h>
#include <gui/canvas.h>

typedef struct {
  Gui* gui;
  View* view;
} HolaApp;

void hola_app_draw_callback(Canvas* canvas, void* context) {
  // Dibujar el texto Hola en el centro de la pantalla
  canvas_set_font(canvas, FontPrimary);
  canvas_draw_str_aligned(canvas, 64, 16, AlignCenter, AlignCenter, "Hola");
}

bool hola_app_input_callback(InputEvent* event, void* context) {
  HolaApp* app = context;
  // Salir de la aplicación si se presiona el botón central
  if(event->type == InputTypeShort && event->key == InputKeyOk) {
    app->view->exit(app->view);
    return true;
  }
  return false;
}

int32_t hola_app(void* p) {
  HolaApp app;
  // Crear la interfaz gráfica
  app.gui = furi_record_open("gui");
  app.view = view_alloc();
  view_allocate_model(app.view, ViewModelTypeLocking, sizeof(HolaApp));
  view_set_context(app.view, &app);
  view_set_draw_callback(app.view, hola_app_draw_callback);
  view_set_input_callback(app.view, hola_app_input_callback);
  view_set_previous_callback(app.view, NULL);
  // Mostrar la vista
  gui_add_view(app.gui, app.view);
  view_dispatcher_run(app.view);
  // Liberar los recursos
  gui_remove_view(app.gui, app.view);
  view_free(app.view);
  furi_record_close("gui");
  return 0;
}