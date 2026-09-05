// #include "screenrecorder.h"

// #include <QGuiApplication>
// #include <QScreen>
// #include <QStandardPaths>
// #include <QDir>
// #include <QDateTime>
// #include <QDebug>


// ScreenRecorder::ScreenRecorder(QObject *parent)
//     : QObject(parent)
//     , m_screenCapture(new QScreenCapture(this))
//     , m_captureSession(new QMediaCaptureSession(this))
//     , m_recorder(new QMediaRecorder(this))
// {
//     // Connect screen capture to media capture session
//     m_captureSession->setScreenCapture(m_screenCapture);

//     // Connect recorder to media capture session
//     m_captureSession->setRecorder(m_recorder);

//     // ---------------------------------------------------------
//     // Configure recording format
//     // ---------------------------------------------------------

//     QMediaFormat format;

//     format.setFileFormat(QMediaFormat::MPEG4);
//     format.setVideoCodec(QMediaFormat::VideoCodec::H264);

//     m_recorder->setMediaFormat(format);

//     // Good general-purpose recording quality
//     m_recorder->setQuality(QMediaRecorder::HighQuality);

//     // ---------------------------------------------------------
//     // Error handling
//     // ---------------------------------------------------------

//     connect(
//         m_screenCapture,
//         &QScreenCapture::errorOccurred,
//         this,
//         &ScreenRecorder::handleScreenCaptureError
//         );

//     connect(
//         m_recorder,
//         &QMediaRecorder::errorOccurred,
//         this,
//         &ScreenRecorder::handleRecorderError
//         );

//     connect(
//         m_recorder,
//         &QMediaRecorder::recorderStateChanged,
//         this,
//         &ScreenRecorder::handleRecorderStateChanged
//         );
// }


// bool ScreenRecorder::startRecording()
// {
//     if (isRecording())
//         return false;

//     // ---------------------------------------------------------
//     // Select the primary monitor
//     // ---------------------------------------------------------

//     QScreen *screen = QGuiApplication::primaryScreen();

//     if (!screen)
//     {
//         emit recordingError("No screen was found.");
//         return false;
//     }

//     m_screenCapture->setScreen(screen);

//     // ---------------------------------------------------------
//     // Create recording directory
//     // ---------------------------------------------------------

//     QString videoDirectory =
//         QStandardPaths::writableLocation(
//             QStandardPaths::MoviesLocation);

//     if (videoDirectory.isEmpty())
//     {
//         videoDirectory =
//             QStandardPaths::writableLocation(
//                 QStandardPaths::DocumentsLocation);
//     }

//     QDir directory(videoDirectory);

//     if (!directory.exists())
//     {
//         if (!directory.mkpath("."))
//         {
//             emit recordingError(
//                 "Unable to create recording directory.");
//             return false;
//         }
//     }

//     // ---------------------------------------------------------
//     // Generate unique file name
//     // ---------------------------------------------------------

//     QString timestamp =
//         QDateTime::currentDateTime()
//             .toString("yyyyMMdd_HHmmss");

//     m_recordingPath =
//         directory.filePath(
//             QString("SLMS_ScreenRecording_%1.mp4")
//                 .arg(timestamp));

//     qDebug() << "Recording file:"
//              << m_recordingPath;

//     // ---------------------------------------------------------
//     // Set recorder output location
//     // ---------------------------------------------------------

//     m_recorder->setOutputLocation(
//         QUrl::fromLocalFile(m_recordingPath));

//     // ---------------------------------------------------------
//     // Start screen capture
//     // ---------------------------------------------------------

//     m_screenCapture->start();

//     // ---------------------------------------------------------
//     // Start recorder
//     // ---------------------------------------------------------

//     m_recorder->record();

//     return true;
// }


// void ScreenRecorder::stopRecording()
// {
//     if (!isRecording())
//         return;

//     // Stop recorder first
//     m_recorder->stop();

//     // Stop screen capture
//     m_screenCapture->stop();
// }


// bool ScreenRecorder::isRecording() const
// {
//     return m_recorder->recorderState()
//     == QMediaRecorder::RecordingState;
// }


// QString ScreenRecorder::recordingPath() const
// {
//     return m_recordingPath;
// }


// void ScreenRecorder::handleScreenCaptureError(
//     QScreenCapture::Error error,
//     const QString &errorString)
// {
//     Q_UNUSED(error);

//     qDebug() << "Screen capture error:"
//              << errorString;

//     emit recordingError(errorString);
// }


// void ScreenRecorder::handleRecorderError(
//     QMediaRecorder::Error error,
//     const QString &errorString)
// {
//     Q_UNUSED(error);

//     qDebug() << "Recorder error:"
//              << errorString;

//     emit recordingError(errorString);
// }


// void ScreenRecorder::handleRecorderStateChanged(
//     QMediaRecorder::RecorderState state)
// {
//     if (state == QMediaRecorder::RecordingState)
//     {
//         qDebug() << "Screen recording started.";

//         emit recordingStarted();
//     }
//     else if (state == QMediaRecorder::StoppedState)
//     {
//         qDebug() << "Screen recording stopped.";

//         emit recordingStopped(m_recordingPath);
//     }
// }


#include "screenrecorder.h"

#include <QGuiApplication>
#include <QScreen>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QDebug>
#include <QUrl>


ScreenRecorder::ScreenRecorder(QObject *parent)
    : QObject(parent)
    , m_screenCapture(new QScreenCapture(this))
    , m_captureSession(new QMediaCaptureSession(this))
    , m_recorder(new QMediaRecorder(this))
{
    // Connect screen capture to media capture session
    m_captureSession->setScreenCapture(m_screenCapture);

    // Connect recorder to media capture session
    m_captureSession->setRecorder(m_recorder);

    // Configure recording format
    QMediaFormat format;

    format.setFileFormat(QMediaFormat::MPEG4);
    format.setVideoCodec(QMediaFormat::VideoCodec::H264);

    m_recorder->setMediaFormat(format);

    // Set recording quality
    m_recorder->setQuality(QMediaRecorder::HighQuality);

    // Error handling
    connect(
        m_screenCapture,
        &QScreenCapture::errorOccurred,
        this,
        &ScreenRecorder::handleScreenCaptureError
        );

    connect(
        m_recorder,
        &QMediaRecorder::errorOccurred,
        this,
        &ScreenRecorder::handleRecorderError
        );

    connect(
        m_recorder,
        &QMediaRecorder::recorderStateChanged,
        this,
        &ScreenRecorder::handleRecorderStateChanged
        );
}


bool ScreenRecorder::startRecording()
{
    if (isRecording())
        return false;

    // Get primary screen
    QScreen *screen = QGuiApplication::primaryScreen();

    if (!screen)
    {
        emit recordingError(
            "No screen was found for screen recording.");

        return false;
    }

    // Set screen to capture
    m_screenCapture->setScreen(screen);

    // Get Movies folder
    QString recordingDirectory =
        QStandardPaths::writableLocation(
            QStandardPaths::MoviesLocation);

    // Fallback to Documents folder
    if (recordingDirectory.isEmpty())
    {
        recordingDirectory =
            QStandardPaths::writableLocation(
                QStandardPaths::DocumentsLocation);
    }

    QDir directory(recordingDirectory);

    if (!directory.exists())
    {
        if (!directory.mkpath("."))
        {
            emit recordingError(
                "Unable to create the recording directory.");

            return false;
        }
    }

    // Create unique file name
    QString timestamp =
        QDateTime::currentDateTime()
            .toString("yyyyMMdd_HHmmss");

    m_recordingPath =
        directory.filePath(
            QString("SLMS_ScreenRecording_%1.mp4")
                .arg(timestamp));

    qDebug() << "Screen recording file:"
             << m_recordingPath;

    // Set output file
    m_recorder->setOutputLocation(
        QUrl::fromLocalFile(m_recordingPath));

    // Start screen capture
    m_screenCapture->start();

    // Start recording
    m_recorder->record();

    return true;
}


void ScreenRecorder::stopRecording()
{
    if (!isRecording())
        return;

    qDebug() << "Stopping screen recording.";

    // Stop recorder first
    m_recorder->stop();

    // Stop screen capture
    m_screenCapture->stop();
}


bool ScreenRecorder::isRecording() const
{
    return m_recorder->recorderState()
    == QMediaRecorder::RecordingState;
}


QString ScreenRecorder::recordingPath() const
{
    return m_recordingPath;
}


void ScreenRecorder::handleScreenCaptureError(
    QScreenCapture::Error error,
    const QString &errorString)
{
    Q_UNUSED(error);

    qDebug() << "Screen capture error:"
             << errorString;

    emit recordingError(errorString);
}


void ScreenRecorder::handleRecorderError(
    QMediaRecorder::Error error,
    const QString &errorString)
{
    Q_UNUSED(error);

    qDebug() << "Media recorder error:"
             << errorString;

    emit recordingError(errorString);
}


void ScreenRecorder::handleRecorderStateChanged(
    QMediaRecorder::RecorderState state)
{
    if (state == QMediaRecorder::RecordingState)
    {
        qDebug() << "Screen recording started.";

        emit recordingStarted();
    }
    else if (state == QMediaRecorder::StoppedState)
    {
        qDebug() << "Screen recording stopped.";

        emit recordingStopped(m_recordingPath);
    }
}