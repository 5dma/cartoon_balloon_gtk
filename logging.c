#define G_LOG_USE_STRUCTURED
#include <glib.h>

/* https://stackoverflow.com/questions/67234569/is-it-possible-to-set-different-writer-functions-per-domain-log-level-in-glib-ne */
GLogWriterOutput
logWriter(GLogLevelFlags log_level,
		  const GLogField *fields,
		  size_t n_fields,
		  void *user_data)

{
	if (log_level & G_LOG_LEVEL_INFO)
	{
		// Do something special with criticals

		// For example purposes, let's just log it to stdout/stderr
		g_info("Info level");

		return G_LOG_WRITER_HANDLED;
	}

	if (log_level & G_LOG_LEVEL_MESSAGE)
	{
		// Do something special with criticals

		// For example purposes, let's just log it to stdout/stderr
		g_message("Message level");

		return G_LOG_WRITER_HANDLED;
	}

	if (log_level & G_LOG_LEVEL_DEBUG)
	{
		// This is not something you should do since it will make
		// debugging harder, but let's just do it for example purposes:
		// by returning G_LOG_WRITER_HANDLED without actually logging it,
		// the log message will not be outputted anywhere
		g_debug("Debug level");
		return G_LOG_WRITER_HANDLED;
	}

	if (log_level & G_LOG_LEVEL_WARNING)
	{
		// Do something special with criticals

		// For example purposes, let's just log it to stdout/stderr
		g_warning("Warning level");
		// return g_log_writer_standard_streams (log_level, fields, n_fields, user_data);
	}

	if (log_level & G_LOG_LEVEL_CRITICAL)
	{
		// Do something special with criticals

		// For example purposes, let's just log it to stdout/stderr
		g_critical("Critical level");
		// return g_log_writer_standard_streams (log_level, fields, n_fields, user_data);
	}

	// If you _really_ want to, you can still check on the GLib domain,
	// as it will be set in one of the GLogFields

	// Default case: use the default logger
	return g_log_writer_default(log_level, fields, n_fields, user_data);
}
