/*!
 *  \file   treeview.h
 *  \author Eva Navratilova
 */

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QGridLayout>
#include <QGraphicsView>
#include <QWheelEvent>
#include <QStyleOptionGraphicsItem>
#include <QPageSize>
#include <QtPrintSupport/QPrinter>

#include "treeview/treescene.h"
#include "treeview/treescenes/treescenenorth.h"
#include "treeview/treescenes/treescenesouth.h"
#include "treeview/treescenes/treesceneuniversal.h"
#include "../../../kernel.h"

class TreeView : public QGraphicsView
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier _proband;

    TreeScene *_scene = nullptr;
    TreeType _type = TreeType::EMPTY;

public:
    TreeView(Kernel &k, Identifier p, QWidget *parent = nullptr);
    ~TreeView();

    void changeProband(Identifier ref);
    void drawTree(TreeType type);
    void drawTree(TreeScene* scene);

    void exportImage(const QString& filename)/* const*/;

    void remove();

private:
    void fill();

    void initScene();
    void drawScene();

    void wheelEvent(QWheelEvent* event);

signals:
    void probandChanged(const Identifier ref);

public slots:
    void exportPdf(const QString& filename) /*const*/;
    void exportBitmap(const QString& filename) const;

private slots:
    void adjustScrollBars();


};

#endif // TREEVIEW_H
