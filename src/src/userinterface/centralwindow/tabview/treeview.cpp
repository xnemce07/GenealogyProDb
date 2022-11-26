/*!
 *  \file   treeview.cpp
 *  \author Eva Navratilova
 */

#include "treeview.h"

TreeView::TreeView(Kernel &k, Identifier p, QWidget *parent)
    : QGraphicsView (parent), _kernel(k), _proband(p)
{
    this->setDragMode(DragMode::ScrollHandDrag);
    this->setRenderHints(/*QPainter::RenderHint::Antialiasing | */QPainter::RenderHint::TextAntialiasing | QPainter::RenderHint::SmoothPixmapTransform);

    this->fill();
}

TreeView::~TreeView()
{
    this->remove();
}

void TreeView::changeProband(Identifier ref)
{
    if(_kernel.record()->isIndividual(ref))
    {
        _proband = ref;
    }

    this->adjustScrollBars();
}

void TreeView::drawTree(TreeType type)
{
    // Initialize & Draw
    _type = type;

    this->initScene();
    this->drawScene();
}

void TreeView::drawTree(TreeScene *scene)
{
    if(_scene != scene)
    {
        // Clear old data
        remove();

        // Initialize & Draw
        _scene = scene;
    }

    this->drawScene();
}

void TreeView::exportImage(const QString &filename) /*const*/
{
    if(_scene != nullptr)
    {
        const QString ext = filename.split(".").last().toLower();
        if(ext == "pdf")
        {
            this->exportPdf(filename);
        }
        else
        {
            this->exportBitmap(filename);
        }
    }
}

void TreeView::fill()
{
    // Initialize

    // Set layout
}

void TreeView::remove()
{
    if(_scene != nullptr)
    {
        _scene->deleteLater();
        _scene = nullptr;
    }
}

/**
 * @brief Initializes _scene member according to the _type member
 *
 * Deletes _scene variable.
 * Constructs a new data for _scene member variable of TreeType
 * according to _type member variable.
 * Decorates it in default fashion.
 *
 */
void TreeView::initScene()
{
    // Clear old data
    this->remove();

    // Init wrappee item (Implementation of TreeScene based on TreeType)
    TreeScene* wrappee = TreeSceneUniversal::sceneForType(_kernel, _proband, _type);

    switch(_type)
    {
    case TreeType::EMPTY:
    case TreeType::ANCESTRAL_OUTLET:
    case TreeType::AGNAT_OUTLET:
    case TreeType::KOGNAT_OUTLET:
        _scene = new TreeSceneNorth(wrappee);
        break;
    case TreeType::FAMILY_TREE:
        _scene = new TreeSceneSouth(wrappee);
        break;
    // Special case - double tree !!!
    case TreeType::RELATIVES_TREE:
        _scene = new TreeSceneNorth(wrappee);
        break;
    }
}

void TreeView::drawScene()
{
    if(_scene != nullptr)
    {
        //_scene->clear();
        _scene->draw();
        this->setScene(_scene->scene());
        this->resetMatrix();
        this->scale(1.0, 1.0);

        connect(_scene->item(), &TreeScene::probandChanged, this, &TreeView::probandChanged);

        this->adjustScrollBars();
    }
}

void TreeView::adjustScrollBars()
{
    if(_scene != nullptr)
    {
        auto node = _scene->getNode(_proband);
        if(node != nullptr)
        {
            auto nodeRect = node->item()->boundingRect();
            qreal xPos = node->item()->x();
            qreal yPos = node->item()->y();
            qreal nodeCenterX = xPos + (nodeRect.width()) / 2;
            qreal nodeCenterY = yPos + (nodeRect.height()) / 2;

            this->centerOn(nodeCenterX, nodeCenterY);
        }
    }
}

void TreeView::wheelEvent(QWheelEvent *event)
{
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        this->scale(scaleFactor, scaleFactor);

    } else {
        // Zoom out
         this->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    //ui->graphicsView->setTransform(QTransform(h11, h12, h21, h22, 0, 0));
}

void TreeView::exportPdf(const QString& filename)/* const*/
{
    QPrinter printer(QPrinter::ScreenResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    printer.setPageMargins(QMargins(10, 10, 10, 10)/*, QPageLayout::Cicero*/);
    printer.setPageSize(QPageSize(QSize(static_cast<int>(_scene->scene()->width()),
                                        static_cast<int>(_scene->scene()->height()))));
    QPainter painter(&printer);
    _scene->scene()->render(&painter, printer.pageRect() /*QRectF(0,0,this->scene.width(), this->scene.height())*//*, QRectF(0,0,this->scene.width(), this->scene.height())*/);

    painter.end();
}

void TreeView::exportBitmap(const QString& filename) const
{
    /// TODO - horrible quality - make it better!!!

    _scene->scene()->clearSelection();                                                   // Selections would also render to the file
    _scene->scene()->setSceneRect(_scene->scene()->itemsBoundingRect());                          // Re-shrink the scene to it's bounding contents
    QImage image(_scene->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);   // Create the image with the exact size of the shrunk scene
    image.fill(Qt::white/*transparent*/);                                       // Start all pixels transparent

    QPainter painter(&image);
    _scene->scene()->render(&painter);
    image.save(filename);
}
