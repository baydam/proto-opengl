#pragma once

#include <QOpenGLWindow>
#include <QOpenGLPaintDevice>
#include <QPainter>
#include <QGLFormat>

class OpenGLWindow : public QOpenGLWindow
{
public:
  OpenGLWindow();
  ~OpenGLWindow();

  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

private:
  // Draw the X Axis line and text
  void drawAbscissa(QPainter &painter);
  // Draw the Y Axis line and text
  void drawOrdinate(QPainter &painter);

  // Abscissa X Axis
  const int X_AXIS_HEIGHT = 60; // From botton to the horizontal line
  const int X_LINE_LEFT_MARGIN = 60; // == Y_AXIS_WIDTH
  const int X_LINE_RIGHT_MARGIN = 30;

  // Ordinate Y Axis
  const int Y_AXIS_WIDTH = 60; // From the left side to the vertical line
  const int Y_LINE_TOP_MARGIN = 30;
  const int Y_LINE_BOTTOM_MARGIN = 60;

  const int X_UNIT = 10; // X Axis interval unit
  const int X_MAX = 100; // Maximun X Axis value

  const int Y_UNIT = 10; // Y Axis interval unit
  const int Y_MAX = 100; // Maximun X Axis value

};
