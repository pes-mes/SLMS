// #ifndef SCREENRECORDER_H
// #define SCREENRECORDER_H

// #include <QObject>
// #include <QScreenCapture>
// #include <QMediaCaptureSession>
// #include <QMediaRecorder>
// #include <QMediaFormat>
// #include <QUrl>

// class ScreenRecorder : public QObject
// {
//     Q_OBJECT

// public:
//     explicit ScreenRecorder(QObject *parent = nullptr);

//     bool startRecording();
//     void stopRecording();

//     bool isRecording() const;

//     QString recordingPath() const;

// signals:
//     void recordingStarted();
//     void recordingStopped(const QString &filePath);
//     void recordingError(const QString &errorMessage);

// private slots:
//     void handleScreenCaptureError(
//         QScreenCapture::Error error,
//         const QString &errorString);

//     void handleRecorderError(
//         QMediaRecorder::Error error,
//         const QString &errorString);

//     void handleRecorderStateChanged(
//         QMediaRecorder::RecorderState state);

// private:
//     QScreenCapture *m_screenCapture;
//     QMediaCaptureSession *m_captureSession;
//     QMediaRecorder *m_recorder;

//     QString m_recordingPath;
// };

// #endif // SCREENRECORDER_H

#ifndef SCREENRECORDER_H
#define SCREENRECORDER_H

#include <QObject>
#include <QScreenCapture>
#include <QMediaCaptureSession>
#include <QMediaRecorder>
#include <QMediaFormat>
#include <QString>

class ScreenRecorder : public QObject
{
    Q_OBJECT

public:
    explicit ScreenRecorder(QObject *parent = nullptr);

    bool startRecording();
    void stopRecording();

    bool isRecording() const;

    QString recordingPath() const;

signals:
    void recordingStarted();
    void recordingStopped(const QString &filePath);
    void recordingError(const QString &errorMessage);

private slots:
    void handleScreenCaptureError(
        QScreenCapture::Error error,
        const QString &errorString);

    void handleRecorderError(
        QMediaRecorder::Error error,
        const QString &errorString);

    void handleRecorderStateChanged(
        QMediaRecorder::RecorderState state);

private:
    QScreenCapture *m_screenCapture;
    QMediaCaptureSession *m_captureSession;
    QMediaRecorder *m_recorder;

    QString m_recordingPath;
};

#endif // SCREENRECORDER_H