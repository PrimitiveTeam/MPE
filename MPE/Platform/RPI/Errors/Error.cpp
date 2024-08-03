#include "MPE/Errors/Error.h"
#include "MPE/MPEPCH.h"
#include "MPE/MPEPLAT.h"

#include <string>

namespace MPE
{
const void Error::showExceptionDialog(const std::exception &e)
{
    std::string errorMessage = "An unhandled exception occurred: ";
    errorMessage += e.what();

    gtk_init(NULL, NULL);
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "%s", errorMessage.c_str());
    gtk_window_set_title(GTK_WINDOW(dialog), "Unhandled Exception");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
}