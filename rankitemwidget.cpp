#include <QPainter>
#include <QPixmap>
#include <QMap>

#include "rankitemwidget.h"
#include "gamelist.h"
#include "settings.h"
#include "macros.h"

extern Gamelist *qmc2Gamelist;
extern Settings *qmc2Config;
extern QMap<QString, QTreeWidgetItem *> qmc2GamelistItemMap;
extern QMap<QString, QTreeWidgetItem *> qmc2HierarchyItemMap;
extern QMap<QString, QTreeWidgetItem *> qmc2CategoryItemMap;
#if defined(QMC2_EMUTYPE_MAME) || defined(QMC2_EMUTYPE_UME)
extern QMap<QString, QTreeWidgetItem *> qmc2VersionItemMap;
#endif

QImage RankItemWidget::rankBackround;
QImage RankItemWidget::rankSingle;
QImage RankItemWidget::rankSingleFlat;
QLinearGradient RankItemWidget::rankGradient;
bool RankItemWidget::useFlatRankImage;
QColor RankItemWidget::rankImageColor;

RankItemWidget::RankItemWidget(QTreeWidgetItem *item, QWidget *parent)
	: QWidget(parent)
{
	m_item = item;
	setupUi(this);
	setMouseTracking(true);
	updateSize();
}

QIcon RankItemWidget::gradientRankIcon()
{
	QPixmap pmRank = QPixmap::fromImage(rankSingle);
	QPainter pRank;
	pRank.begin(&pmRank);
	pRank.setCompositionMode(QPainter::CompositionMode_Overlay);
	pRank.fillRect(pmRank.rect(), rankImageColor);
	pRank.end();
	return QIcon(pmRank);
}

QIcon RankItemWidget::flatRankIcon()
{
	QPixmap pmRank = QPixmap::fromImage(rankSingleFlat);
	QPainter pRank;
	pRank.begin(&pmRank);
	pRank.setCompositionMode(QPainter::CompositionMode_Overlay);
	pRank.fillRect(pmRank.rect(), rankImageColor);
	pRank.end();
	return QIcon(pmRank);
}

void RankItemWidget::updateSize(QFontMetrics *fm)
{
	QSize newSize = size();
	if ( fm )
		newSize.scale(width(), fm->height(), Qt::KeepAspectRatio);
	else
		newSize.scale(width(), fontMetrics().height(), Qt::KeepAspectRatio);
	setFixedSize(newSize);
	QTimer::singleShot(0, this, SLOT(updateRankFromDb()));
}

void RankItemWidget::setRank(int rank)
{
	QPixmap pm(rankBackround.size());
	pm.fill(Qt::transparent);
	QPainter p;
	p.begin(&pm);
	p.setBrush(rankGradient);
	m_rank = rank;
	m_item->setWhatsThis(QMC2_GAMELIST_COLUMN_RANK, QString::number(m_rank));
	QPixmap pmRank = useFlatRankImage ? QPixmap::fromImage(rankSingleFlat) : QPixmap::fromImage(rankSingle);
	QPainter pRank;
	pRank.begin(&pmRank);
	pRank.setCompositionMode(QPainter::CompositionMode_Overlay);
	pRank.fillRect(pmRank.rect(), rankImageColor);
	pRank.end();
	for (int r = 0; r < m_rank; r++) {
		int x = r * rankSingle.width();
		p.drawPixmap(x, 0, pmRank);
		p.drawRoundedRect(x + 2, 3, rankSingle.width() - 2, rankSingle.height() - 3, 5, 5, Qt::RelativeSize);
	}
	QPixmap pmBackground = QPixmap::fromImage(rankBackround);
	QPainter pBackground;
	pBackground.begin(&pmBackground);
	pBackground.setCompositionMode(QPainter::CompositionMode_SourceIn);
	pBackground.fillRect(pmBackground.rect(), m_item->treeWidget()->palette().color(QPalette::Text));
	pBackground.end();
	p.drawPixmap(0, 0, pmBackground);
	p.end();
	rankImage->setPixmap(pm.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void RankItemWidget::increaseRank()
{
	int newRank = m_rank + 1;
	if ( newRank < 6 ) {
		setRank(newRank);
		qmc2Gamelist->userDataDb()->setRank(m_item->text(QMC2_GAMELIST_COLUMN_NAME), m_rank);
		updateForeignItems();
	}
}

void RankItemWidget::decreaseRank()
{
	int newRank = m_rank - 1;
	if ( newRank >= 0 ) {
		setRank(newRank);
		qmc2Gamelist->userDataDb()->setRank(m_item->text(QMC2_GAMELIST_COLUMN_NAME), m_rank);
		updateForeignItems();
	}
}

void RankItemWidget::updateRankFromDb()
{
	setRank(qmc2Gamelist->userDataDb()->rank(m_item->text(QMC2_GAMELIST_COLUMN_NAME)));
}

void RankItemWidget::updateRankFromMousePos(int mouseX)
{
	setRank(int(0.5f + 6.0f * (double)mouseX / (double)(width())));
	qmc2Gamelist->userDataDb()->setRank(m_item->text(QMC2_GAMELIST_COLUMN_NAME), m_rank);
	updateForeignItems();
}

void RankItemWidget::mousePressEvent(QMouseEvent *e)
{
	if ( e->buttons() & Qt::LeftButton )
		if ( rect().contains(e->pos()) )
			updateRankFromMousePos(e->x());
}

void RankItemWidget::mouseMoveEvent(QMouseEvent *e)
{
	if ( e->buttons() & Qt::LeftButton )
		if ( rect().contains(e->pos()) )
			updateRankFromMousePos(e->x());
}

void RankItemWidget::updateForeignItems()
{
	RankItemWidget *foreignRiw;
	QString myId = m_item->text(QMC2_GAMELIST_COLUMN_NAME);
	QTreeWidgetItem *item = qmc2GamelistItemMap[myId];
	if ( item && item != m_item ) {
		foreignRiw = (RankItemWidget *)item->treeWidget()->itemWidget(item, QMC2_GAMELIST_COLUMN_RANK);
		if ( foreignRiw )
			foreignRiw->setRank(m_rank);
	}
	item = qmc2HierarchyItemMap[myId];
	if ( item && item != m_item ) {
		foreignRiw = (RankItemWidget *)item->treeWidget()->itemWidget(item, QMC2_GAMELIST_COLUMN_RANK);
		if ( foreignRiw )
			foreignRiw->setRank(m_rank);
	}
	item = qmc2CategoryItemMap[myId];
	if ( item && item != m_item ) {
		foreignRiw = (RankItemWidget *)item->treeWidget()->itemWidget(item, QMC2_GAMELIST_COLUMN_RANK);
		if ( foreignRiw )
			foreignRiw->setRank(m_rank);
	}
#if defined(QMC2_EMUTYPE_MAME) || defined(QMC2_EMUTYPE_UME)
	item = qmc2VersionItemMap[myId];
	if ( item && item != m_item ) {
		foreignRiw = (RankItemWidget *)item->treeWidget()->itemWidget(item, QMC2_GAMELIST_COLUMN_RANK);
		if ( foreignRiw )
			foreignRiw->setRank(m_rank);
	}
#endif
}
