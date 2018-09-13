/****************************************************************************
** Copyright (C) 2018 Olaf Japp
**
** This file is part of AnimationMaker.
**
**  AnimationMaker is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  AnimationMaker is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with AnimationMaker.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include "sceneview.h"
#include "animationscene.h"
#include "ruler.h"
#include <QGridLayout>

SceneView::SceneView(AnimationScene *scene)
    : QGraphicsView (scene)
{
    setMouseTracking(true);
    setViewportMargins(20, 20, 0, 0);
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setMargin(0);

    m_horizontalRuler = new Ruler(Ruler::Horizontal);
    m_verticalRuler = new Ruler(Ruler::Vertical);

    QWidget* corner = new QWidget();
    corner->setBackgroundRole(QPalette::Window);
    corner->setFixedSize(20, 20);
    gridLayout->addWidget(corner, 0, 0);
    gridLayout->addWidget(m_horizontalRuler, 0, 1);
    gridLayout->addWidget(m_verticalRuler, 1, 0);
    gridLayout->addWidget(viewport(), 1, 1);

    setLayout(gridLayout);
}

void SceneView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pt = mapToScene(event->pos());
    m_horizontalRuler->setCursorPos(pt.toPoint());
    m_verticalRuler->setCursorPos(pt.toPoint());
    QGraphicsView::mouseMoveEvent(event);
}

void SceneView::scrollContentsBy(int dx, int dy)
{
    QGraphicsView::scrollContentsBy(dx, dy);

    QPointF p1(mapToScene(QPoint(0, 0)));
    QPointF p2(mapToScene(QPoint(viewport()->width(), viewport()->height())));
    QRectF  r(p1, p2);

    m_horizontalRuler->setScaledRect(r);
    m_verticalRuler->setScaledRect(r);
}
