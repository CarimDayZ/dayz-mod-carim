#ifndef CARIM_CarimLogging
#define CARIM_CarimLogging

enum CarimLoggingLevel {
    NONE = 0,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
}

class CarimLogging extends Managed {
    static ref CarimModelSettings settings;

    static void LogMessage(CarimLoggingLevel level, Class context, string message) {
        if (WillLog(level)) {
            string levelName = typename.EnumToString(CarimLoggingLevel, level);
            string contextName = context.ClassName();
            Print("[Carim - " + levelName + " - " + contextName + "] " + message);
        }
    }

    static void Error(Class context, string message) {
        LogMessage(CarimLoggingLevel.ERROR, context, message);
    }

    static bool ErrorEnabled() {
        return WillLog(CarimLoggingLevel.ERROR);
    }

    static void Warn(Class context, string message) {
        LogMessage(CarimLoggingLevel.WARN, context, message);
    }

    static bool WarnEnabled() {
        return WillLog(CarimLoggingLevel.WARN);
    }

    static void Info(Class context, string message) {
        LogMessage(CarimLoggingLevel.INFO, context, message);
    }

    static bool InfoEnabled() {
        return WillLog(CarimLoggingLevel.INFO);
    }

    static void Debug(Class context, string message) {
        LogMessage(CarimLoggingLevel.DEBUG, context, message);
    }

    static bool DebugEnabled() {
        return WillLog(CarimLoggingLevel.DEBUG);
    }

    static void Trace(Class context, string message) {
        LogMessage(CarimLoggingLevel.TRACE, context, message);
    }

    static bool TraceEnabled() {
        return WillLog(CarimLoggingLevel.TRACE);
    }

    static bool WillLog(CarimLoggingLevel level) {
        if (!settings) {
            return true;
        }
        // TODO
        return true;
        return settings.verbosity >= level;
    }
}

#endif
