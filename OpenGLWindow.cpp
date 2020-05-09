#include "OpenGLWindow.h"

OpenGLWindow::OpenGLWindow()
{
  QSurfaceFormat format;
  format.setSamples(16);
  setFormat(format);
}

void OpenGLWindow::initializeGL()
{
  glClearColor(0, 0, 0, 0);

  glEnable(GL_DEBUG_OUTPUT); // Debug messages are produced by a debug context
  glEnable(GL_MULTISAMPLE); // Enable antialiasing
}

void OpenGLWindow::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
}

void OpenGLWindow::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QOpenGLPaintDevice device;
  device.setSize(QSize(width(), height()));
  QPainter painter(&device);
  /* NOTE: The default coordinate system of a paint device
   * has its origin at the top-left corner.
   * The X values increase to the right and the Y values increase downwards
   */
  painter.setPen(QColor(255, 255, 255));
  painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
  // Draw the X Axis line and text
  drawAbscissa(painter);
  // Draw the Y Axis line and text
  drawOrdinate(painter);

  painter.beginNativePainting(); // Start OpenGL drawing
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();

  glBegin(GL_QUADS);
      glColor4f(255, 0, 0, 255);
      glVertex2f(300,300);
      glVertex2f(500,300);
      glVertex2f(500,500);
      glVertex2f(300,500);
  glEnd();

  glPopMatrix();
  painter.endNativePainting(); // Finish OpenGL drawing
}

void OpenGLWindow::drawAbscissa(QPainter &painter)
{
  painter.save(); // Push Matrix
  int lineWidth = width() - (X_LINE_LEFT_MARGIN + X_LINE_RIGHT_MARGIN);
  int interval = X_MAX / X_UNIT;
  QRect xAxisTextRect(0, 0, lineWidth / interval, X_AXIS_HEIGHT);
  painter.drawLine(QPoint(X_LINE_LEFT_MARGIN, height() - X_AXIS_HEIGHT),
                   QPoint(width() - X_LINE_RIGHT_MARGIN, height() - X_AXIS_HEIGHT));
  painter.translate(X_LINE_LEFT_MARGIN, height() - X_AXIS_HEIGHT);
  for (int xAxis = X_UNIT; xAxis <= X_MAX; xAxis += X_UNIT) {
    painter.drawText(xAxisTextRect, Qt::AlignRight | Qt::AlignVCenter, QString::number(xAxis));
        painter.translate(lineWidth / interval, 0);
  }
  painter.restore(); // Pop Matrix
}

void OpenGLWindow::drawOrdinate(QPainter &painter)
{
  painter.save(); // Push Matrix
  int lineHeight = height() - (Y_LINE_TOP_MARGIN + Y_LINE_BOTTOM_MARGIN);
  int interval = Y_MAX / Y_UNIT;
  QRect yAxisTextRect(0, 0, Y_AXIS_WIDTH, lineHeight / interval);
  painter.drawLine(QPoint(Y_AXIS_WIDTH, Y_LINE_TOP_MARGIN),
                   QPoint(Y_AXIS_WIDTH, height() - Y_LINE_BOTTOM_MARGIN));
  painter.translate(0, Y_LINE_TOP_MARGIN);
  for (int yAxis = Y_MAX; yAxis >= Y_UNIT; yAxis -= Y_UNIT) {
    painter.drawText(yAxisTextRect, Qt::AlignTop | Qt::AlignHCenter, QString::number(yAxis));
    painter.translate(0, lineHeight / interval);
  }
  painter.restore(); // Pop Matrix
}

OpenGLWindow::~OpenGLWindow()
{
  makeCurrent();
}
